#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "proto/system.grpc.pb.h"
#include "proto/system.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using param::MemoryManagerService;
using param::MPointerRequest;
using param::MemoryManagerReply;

class MemoryManagerServiceImpl final : public MemoryManagerService::Service {
    
    Status MPointerOperation(ServerContext* context, const MPointerRequest* request, MemoryManagerReply* reply) override {
        std::string received_message = request->message();
        std::cout << "mem-mgr input " << received_message << std::endl;

        reply->set_message("succesfully");
        return Status::OK;
    }
};

void ManagerInit(std::string listen_port) { // mem-mgr Initializer 
    MemoryManagerServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(listen_port, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "LISTEN_PORT " << listen_port << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    std::string listen_port = "0.0.0.0:" + std::string(argv[1]);
    ManagerInit(listen_port);
    return 0;
}
