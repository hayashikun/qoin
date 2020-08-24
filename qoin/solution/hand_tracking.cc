#include "mediapipe/framework/formats/detection.pb.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "qoin/solution/solution.h"

constexpr char kOutputPalm[] = "palm_detections";
constexpr char kOutputHand[] = "hand_landmarks";

namespace qoin {
class HandTrackingSolutionImpl : public Solution {
 public:
  HandTrackingSolutionImpl() {
    calculator_graph_config_file_ = "graphs/hand_tracking_desktop_live.pbtxt";
  }

  void RegisterOutputStreamHandler(mediapipe::CalculatorGraph &graph) {
    graph.ObserveOutputStream(kOutputPalm, [&](const mediapipe::Packet &p) {
      auto &data = p.Get<std::vector<mediapipe::Detection>>();
      for (int i = 0; i < data.size(); i++) {
        LOG(INFO) << data[i].DebugString();
      }
      return ::mediapipe::OkStatus();
    });

    graph.ObserveOutputStream(kOutputHand, [&](const mediapipe::Packet &p) {
      auto &data = p.Get<mediapipe::NormalizedLandmarkList>();
      LOG(INFO) << data.DebugString();
      return ::mediapipe::OkStatus();
    });
  }
};
}  // namespace qoin

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  qoin::HandTrackingSolutionImpl solution;
  ::mediapipe::Status run_status = solution.StartVideo();
  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
    return EXIT_FAILURE;
  } else {
    LOG(INFO) << "Success!";
  }
  return EXIT_SUCCESS;
}
