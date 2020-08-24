#include "mediapipe/framework/formats/landmark.pb.h"
#include "qoin/solution/solution.h"

constexpr char kOutputLandmarks[] = "multi_face_landmarks";

namespace qoin {
class FaceMeshSolutionImpl : public Solution {
 public:
  FaceMeshSolutionImpl() {
    calculator_graph_config_file_ = "graphs/face_mesh_desktop_live.pbtxt";
  }

  void RegisterOutputStreamHandler(mediapipe::CalculatorGraph &graph) {
    graph.ObserveOutputStream(
        kOutputLandmarks, [&](const mediapipe::Packet &p) {
          auto &landmarks =
              p.Get<std::vector<mediapipe::NormalizedLandmarkList>>();
          for (int i = 0; i < landmarks.size(); i++) {
            LOG(INFO) << landmarks[i].DebugString();
          }
          return ::mediapipe::OkStatus();
        });
  }
};
}  // namespace qoin

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  qoin::FaceMeshSolutionImpl solution;
  ::mediapipe::Status run_status = solution.StartVideo();
  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
    return EXIT_FAILURE;
  } else {
    LOG(INFO) << "Success!";
  }
  return EXIT_SUCCESS;
}
