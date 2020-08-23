#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "qoin/proto/hello.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(qoin::Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    qoin::HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    qoin::HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string SayHelloAgain(const std::string& user) {
    // Follows the same pattern as SayHello.
    qoin::HelloRequest request;
    request.set_name(user);
    qoin::HelloReply reply;
    ClientContext context;

    // Here we can use the stub's newly available method we just added.
    Status status = stub_->SayHelloAgain(&context, request, &reply);
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<qoin::Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  std::string address = "localhost";
  std::string port = "50051";
  std::string server_address = address + ":" + port;
  std::cout << "Client querying server address: " << server_address
            << std::endl;

  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  GreeterClient greeter(
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
  std::string user("world");

  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;

  reply = greeter.SayHelloAgain(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}