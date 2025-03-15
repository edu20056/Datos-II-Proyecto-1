#include <grpcpp/grpcpp.h>
#include <proto/hello.grpc.pb.h>
#include <proto/hello.pb.h>  

// Implementación del servicio
class ProcessingImpl : public ProcessingServices::Service {
public:
    grpc::Status computeSum(grpc::ServerContext* context, const Point3* request, Numeric* response) override {
        std::cout << "Called!" << std::endl;
        response->set_value(request->x() + request->y() + request->z());
        return grpc::Status::OK;
    }
};

int main() {
    // Crear e inicializar el servicio
    ProcessingImpl service;
    
    grpc::ServerBuilder builder;
    
    // Configurar el puerto y las credenciales
    builder.AddListeningPort("0.0.0.0:9999", grpc::InsecureServerCredentials());
    
    // Registrar el servicio
    builder.RegisterService(&service);

    // Crear y comenzar el servidor
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    
    // Esperar a que el servidor termine
    server->Wait();

    return 0;
}
