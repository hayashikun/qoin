#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>
#include "qoin/client/grpc_client.h"

DEFINE_string(url, "", "gRPC sever URL");

namespace qoin {
std::shared_ptr<grpc::Channel> connect() {
        return grpc::CreateChannel(FLAGS_url, grpc::InsecureChannelCredentials());
}
}  // namespace qoin