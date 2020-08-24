#include <string>

#include "mediapipe/framework/calculator_framework.h"

namespace qoin {
class Solution {
 public:
  ::mediapipe::Status StartVideo();
  virtual void RegisterOutputStreamHandler(
      mediapipe::CalculatorGraph& graph) = 0;

protected:
  std::string calculator_graph_config_file_;
};
}  // namespace qoin