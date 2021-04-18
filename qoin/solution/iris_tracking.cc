#include "mediapipe/framework/formats/landmark.pb.h"
#include "qoin/solution/solution.h"

constexpr char kOutputLandmarks[] = "iris_landmarks";

namespace qoin {
    class IrisTrackingSolutionImpl : public Solution {
    public:
        IrisTrackingSolutionImpl() {
            calculator_graph_config_file_ = "graphs/iris_tracking_cpu.pbtxt";
        }

        void RegisterOutputStreamHandler(mediapipe::CalculatorGraph &graph) override {
            graph.ObserveOutputStream(kOutputLandmarks, [&](const mediapipe::Packet &p) {
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
    qoin::IrisTrackingSolutionImpl solution;
    ::mediapipe::Status run_status = solution.StartVideo();
    if (!run_status.ok()) {
        LOG(ERROR) << "Failed to run the graph: " << run_status.message();
        return EXIT_FAILURE;
    } else {
        LOG(INFO) << "Success!";
    }
    return EXIT_SUCCESS;
}
