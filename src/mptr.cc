#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "proto/system.grpc.pb.h"
#include "proto/system.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using param::MemoryManagerService;
using param::MPointerRequest;
using param::MemoryManagerReply;

class MPointer {
public:
    MPointer(std::shared_ptr<Channel> channel) : stub_(MemoryManagerService::NewStub(channel)) {}

    std::string MPointerOperation(const std::string& user_message) {
        MPointerRequest request;
        request.set_message(user_message);

        MemoryManagerReply reply;
        ClientContext context;

        Status status = stub_->MPointerOperation(&context, request, &reply);

        if (status.ok()) {
            return reply.message();
        } else {
            return status.error_message();
        }
    }

private:
    std::unique_ptr<MemoryManagerService::Stub> stub_;
};

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server:port> <message>" << std::endl;
        return 1;
    }

    std::string server_address = argv[1];
    std::string user_message = argv[2];

    MPointer client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
    std::string response = client.MPointerOperation(user_message);
    std::cout << "mem-mgr output " << response << std::endl;

    return 0;
}