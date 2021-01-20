#include <grpcpp/grpcpp.h>

namespace qoin {
    std::shared_ptr<grpc::Channel> connect();
}  // namespace qoin