#include <grpcpp/grpcpp.h>

#include <thread>

#include "mediapipe/framework/formats/landmark.pb.h"
#include "qoin/client/grpc_client.h"
#include "qoin/proto/face_mesh.grpc.pb.h"
#include "qoin/solution/solution.h"

constexpr char kOutputLandmarks[] = "multi_face_landmarks";

namespace qoin {
    std::unique_ptr<grpc::ClientWriter<FaceMeshPushRequest>> grpc_writer;
    bool solution_running = false;
    bool writing_status = true;
    std::mutex mtx;

    class FaceMeshClient {
    public:
        explicit FaceMeshClient(const std::shared_ptr<grpc::Channel> &channel)
                : stub_(FaceMesh::NewStub(channel)) {}

        void FaceMeshPushStream() {
            grpc::ClientContext context;
            FaceMeshPushReply response;

            std::unique_ptr<grpc::ClientWriter<FaceMeshPushRequest>> writer(
                    stub_->FaceMeshPushStream(&context, &response));

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
        std::unique_ptr<qoin::FaceMesh::Stub> stub_;
    };

    class FaceMeshSolutionClientImpl : public Solution {
    public:
        FaceMeshSolutionClientImpl() {
            calculator_graph_config_file_ = "graphs/face_mesh_desktop_live.pbtxt";
        }

        void RegisterOutputStreamHandler(mediapipe::CalculatorGraph &graph) override {
            graph.ObserveOutputStream(
                    kOutputLandmarks, [&](const mediapipe::Packet &p) {
                        {
                            std::lock_guard<std::mutex> lock(mtx);
                            if (grpc_writer != nullptr) {
                                auto &landmark_lists =
                                        p.Get<std::vector<mediapipe::NormalizedLandmarkList>>();
                                FaceMeshPushRequest request;
                                for (const auto &landmark_list : landmark_lists) {
                                    request.add_landmark_list()->CopyFrom(landmark_list);
                                }
                                writing_status = grpc_writer->Write(request);
                            }
                        }
                        return ::mediapipe::OkStatus();
                    });
        }
    };

    void StartSolution() {
        qoin::FaceMeshSolutionClientImpl solution;
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
        FaceMeshClient client(connect());
        while (!solution_running) {
        }  // wait until solution start
        client.FaceMeshPushStream();
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
