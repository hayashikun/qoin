#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "mediapipe/framework/formats/rect.pb.h"
#include "qoin/proto/hello.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public qoin::Greeter::Service {
  Status SayHello(ServerContext* context, const qoin::HelloRequest* request,
                  qoin::HelloReply* reply) override {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }

  Status SayHelloAgain(ServerContext* context,
                       const qoin::HelloRequest* request,
                       qoin::HelloReply* reply) override {
    std::string prefix("Hello again ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }

  Status GetRect(ServerContext* context, const qoin::RectRequest* request,
                 qoin::RectReply* reply) override {
    mediapipe::Rect rect;
    rect.set_x_center(0);
    reply->mutable_rect()->CopyFrom(rect);
    return Status::OK;
  }
};

void RunServer() {
  std::string address = "0.0.0.0";
  std::string port = "50051";
  std::string server_address = address + ":" + port;
  GreeterServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}