#include <grpcpp/grpcpp.h>

#include <thread>

#include "mediapipe/framework/formats/landmark.pb.h"
#include "qoin/client/grpc_client.h"
#include "qoin/proto/iris_tracking.grpc.pb.h"
#include "qoin/solution/solution.h"


constexpr char kOutputLandmarks[] = "iris_landmarks";


namespace qoin {
    std::unique_ptr<grpc::ClientWriter<IrisTrackingPushRequest>> grpc_writer;
    bool solution_running = false;
    bool writing_status = true;
    std::mutex mtx;

    class IrisTrackingClient {
    public:
        explicit IrisTrackingClient(const std::shared_ptr<grpc::Channel> &channel)
                : stub_(IrisTracking::NewStub(channel)) {}

        void IrisTrackingPushStream() {
            grpc::ClientContext context;
            IrisTrackingPushReply response;

            std::unique_ptr<grpc::ClientWriter<IrisTrackingPushRequest>> writer(
                    stub_->IrisTrackingPushStream(&context, &response));

            grpc_writer = std::move(writer);
            while (solution_running) {
                if (!writing_status) break;
            }
            grpc_writer->WritesDone();
            grpc_writer->Finish();
            {
                std::lock_guard<std::mutex> lock(mtx);
                grpc_writer = nullptr;
            }
        }

    private:
        std::unique_ptr<qoin::IrisTracking::Stub> stub_;
    };

    class IrisTrackingSolutionClientImpl : public Solution {
    public:
        IrisTrackingSolutionClientImpl() {
            calculator_graph_config_file_ = "graphs/iris_tracking_cpu.pbtxt";
        }

        void RegisterOutputStreamHandler(mediapipe::CalculatorGraph &graph) override {
            graph.ObserveOutputStream(kOutputLandmarks, [&](const mediapipe::Packet &p) {
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (grpc_writer != nullptr) {
                        auto &landmark_list = p.Get<mediapipe::NormalizedLandmarkList>();
                        IrisTrackingPushRequest request;
                        request.mutable_landmark_list()->CopyFrom(landmark_list);
                        writing_status = grpc_writer->Write(request);
                    }
                }
                return ::mediapipe::OkStatus();
            });
        }
    };

    void StartSolution() {
        qoin::IrisTrackingSolutionClientImpl solution;
        solution_running = true;
        ::mediapipe::Status run_status = solution.StartVideo();
        solution_running = false;
        if (!run_status.ok()) {
            LOG(ERROR) << "Failed to run the graph: " << run_status.message();
        } else {
            LOG(INFO) << "Success!";
        }
    }

    void StartClient() {
        IrisTrackingClient client(connect());
        while (!solution_running) {
        }  // wait until solution start
        client.IrisTrackingPushStream();
    }
}  // namespace qoin

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::thread th_client(qoin::StartClient);
    qoin::StartSolution();
    th_client.join();
    return 0;
}
