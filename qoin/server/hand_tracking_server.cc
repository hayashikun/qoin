#include <grpcpp/grpcpp.h>

#include <thread>

#include "qoin/proto/hand_tracking.grpc.pb.h"
#include "qoin/solution/solution.h"
#include "mediapipe/framework/formats/detection.pb.h"
#include "mediapipe/framework/formats/landmark.pb.h"

constexpr char kOutputPalm[] = "palm_detections";
constexpr char kOutputHand[] = "hand_landmarks";

namespace qoin {
grpc::ServerWriter<HandTrackingReply>* grpc_writer;
bool solution_running = false;

class HandTrackingSolutionServerImpl : public Solution {
 public:
  HandTrackingSolutionServerImpl() {
    calculator_graph_config_file_ = "graphs/hand_tracking_desktop_live.pbtxt";
  }

  void RegisterOutputStreamHandler(mediapipe::CalculatorGraph& graph) {
    graph.ObserveOutputStream(kOutputHand, [&](const mediapipe::Packet &p) {
      if (grpc_writer != nullptr) {
        auto &landmark_list = p.Get<mediapipe::NormalizedLandmarkList>();
        qoin::HandTrackingReply reply;
        for (int i = 0; i < landmark_list.landmark_size(); i++) {
          qoin::Landmark* landmark = reply.mutable_landmark_list()->add_landmark();
          landmark->set_x(landmark_list.landmark(i).x());
          landmark->set_y(landmark_list.landmark(i).y());
          landmark->set_z(landmark_list.landmark(i).z());
        }
        grpc_writer->Write(reply);
      }
      return ::mediapipe::OkStatus();
    });
  }
};

void StartSolution() {
  qoin::HandTrackingSolutionServerImpl solution;
  solution_running = true;
  ::mediapipe::Status run_status = solution.StartVideo();
  solution_running = false;
  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
  } else {
    LOG(INFO) << "Success!";
  }
}

class HandTrackingServiceImpl final : public HandTracking::Service {
 public:
  grpc::Status HandTrackingStream(grpc::ServerContext* context,
                              const HandTrackingRequest* request,
                              grpc::ServerWriter<HandTrackingReply>* writer) {
    grpc_writer = writer;
    while (solution_running){}    
  }
};

void StartServer() {
  std::string address = "0.0.0.0";
  std::string port = "50051";
  std::string server_address = address + ":" + port;
  qoin::HandTrackingServiceImpl service;
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
