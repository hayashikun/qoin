#include <grpcpp/grpcpp.h>

#include <thread>

#include "mediapipe/framework/formats/landmark.pb.h"
#include "qoin/proto/iris_tracking.grpc.pb.h"
#include "qoin/solution/solution.h"

constexpr char kOutputLandmarks[] = "iris_landmarks";

namespace qoin {
    grpc::ServerWriter<IrisTrackingPullReply> *grpc_writer;
    std::unique_ptr<grpc::Server> server;
    bool solution_running = false;
    std::mutex mtx;

    class IrisTrackingSolutionServerImpl : public Solution {
    public:
        IrisTrackingSolutionServerImpl() {
            calculator_graph_config_file_ = "graphs/iris_tracking_cpu.pbtxt";
        }

        void RegisterOutputStreamHandler(mediapipe::CalculatorGraph &graph) override {
            graph.ObserveOutputStream(kOutputLandmarks, [&](const mediapipe::Packet &p) {
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (grpc_writer != nullptr) {
                        auto &landmark_list = p.Get<mediapipe::NormalizedLandmarkList>();
                        qoin::IrisTrackingPullReply reply;
                        reply.mutable_landmark_list()->CopyFrom(landmark_list);
                        grpc_writer->Write(reply);
                    }
                }
                return ::mediapipe::OkStatus();
            });
        }
    };

    void StartSolution() {
        qoin::IrisTrackingSolutionServerImpl solution;
        solution_running = true;
        ::mediapipe::Status run_status = solution.StartVideo();
        solution_running = false;
        if (!run_status.ok()) {
            LOG(ERROR) << "Failed to run the graph: " << run_status.message();
        } else {
            LOG(INFO) << "Success!";
        }
    }

    class IrisTrackingServiceImpl final : public IrisTracking::Service {
    public:
        grpc::Status IrisTrackingPullStream(
                grpc::ServerContext *context, const IrisTrackingPullRequest *request,
                grpc::ServerWriter<IrisTrackingPullReply> *writer) override {
            grpc_writer = writer;
            while (solution_running) {
                if (context->IsCancelled()) {
                    break;
                }
            }
            {
                std::lock_guard<std::mutex> lock(mtx);
                grpc_writer = nullptr;
            }
            return grpc::Status::OK;
        }
    };

    void StartServer() {
        std::string address = "0.0.0.0";
        std::string port = "50051";
        std::string server_address = address + ":" + port;
        qoin::IrisTrackingServiceImpl service;
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        server = builder.BuildAndStart();
        std::cout << "Server listening on " << server_address << std::endl;
        server->Wait();
    }
}  // namespace qoin

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::thread th_server(qoin::StartServer);
    qoin::StartSolution();
    qoin::server->Shutdown();
    th_server.join();

    return 0;
}
