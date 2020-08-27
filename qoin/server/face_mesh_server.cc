#include <grpcpp/grpcpp.h>

#include <thread>

#include "mediapipe/framework/formats/landmark.pb.h"
#include "qoin/proto/face_mesh.grpc.pb.h"
#include "qoin/proto/face_mesh.pb.h"
#include "qoin/solution/solution.h"

constexpr char kOutputLandmarks[] = "multi_face_landmarks";

namespace qoin {
grpc::ServerWriter<FaceMeshReply>* grpc_writer;
bool solution_running = false;

class FaceMeshSolutionServerImpl : public Solution {
 public:
  FaceMeshSolutionServerImpl() {
    calculator_graph_config_file_ = "graphs/face_mesh_desktop_live.pbtxt";
  }

  void RegisterOutputStreamHandler(mediapipe::CalculatorGraph& graph) {
    graph.ObserveOutputStream(
        kOutputLandmarks, [&](const mediapipe::Packet& p) {
          if (grpc_writer != nullptr) {
            auto& landmark_lists =
                p.Get<std::vector<mediapipe::NormalizedLandmarkList>>();
            qoin::FaceMeshReply reply;
            for (int i = 0; i < landmark_lists.size(); i++) {
              *reply.add_landmark_list() = landmark_lists[i];
            }
            grpc_writer->Write(reply);
          }
          return ::mediapipe::OkStatus();
        });
  }
};

void StartSolution() {
  qoin::FaceMeshSolutionServerImpl solution;
  solution_running = true;
  ::mediapipe::Status run_status = solution.StartVideo();
  solution_running = false;
  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
  } else {
    LOG(INFO) << "Success!";
  }
}

class FaceMeshServiceImpl final : public FaceMesh::Service {
 public:
  grpc::Status FaceMeshStream(grpc::ServerContext* context,
                              const FaceMeshRequest* request,
                              grpc::ServerWriter<FaceMeshReply>* writer) {
    grpc_writer = writer;
    while (solution_running) {
    }
  }
};

void StartServer() {
  std::string address = "0.0.0.0";
  std::string port = "50051";
  std::string server_address = address + ":" + port;
  qoin::FaceMeshServiceImpl service;
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}
}  // namespace qoin

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::thread th_server(qoin::StartServer);
  qoin::StartSolution();
  th_server.join();

  return 0;
}
