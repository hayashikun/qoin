#include <grpcpp/grpcpp.h>

#include "qoin/proto/face_mesh.grpc.pb.h"
#include "qoin/solution/solution.h"

constexpr char kOutputLandmarks[] = "multi_face_landmarks";

namespace qoin {
class FaceMeshSolutionServerImpl : public Solution {
 public:
  grpc::ServerWriter<FaceMeshReply>* grpc_writer;

  FaceMeshSolutionServerImpl() {
    calculator_graph_config_file_ = "graphs/face_mesh_desktop_live.pbtxt";
  }

  void RegisterOutputStreamHandler(mediapipe::CalculatorGraph& graph) {
    graph.ObserveOutputStream(kOutputLandmarks,
                              [&](const mediapipe::Packet& p) {
                                if (grpc_writer != nullptr) {
                                  //qoin::FaceMeshReply reply;
                                  //grpc_writer->Write(reply);
                                }
                                return ::mediapipe::OkStatus();
                              });
  }
};

class FaceMeshServiceImpl final : public FaceMesh::Service {
 public:
  FaceMeshSolutionServerImpl* solution;
  grpc::Status FaceMeshStream(grpc::ServerContext* context,
                              const FaceMeshRequest* request,
                              grpc::ServerWriter<FaceMeshReply>* writer) {
    solution->grpc_writer = writer;
  }
};
}  // namespace qoin

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::string address = "0.0.0.0";
  std::string port = "50051";
  std::string server_address = address + ":" + port;
  qoin::FaceMeshServiceImpl service;
  qoin::FaceMeshSolutionServerImpl solution;
  service.solution = &solution;
  ::mediapipe::Status run_status = solution.StartVideo();
  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
    return EXIT_FAILURE;
  } else {
    LOG(INFO) << "Success!";
  }

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return EXIT_SUCCESS;
}
