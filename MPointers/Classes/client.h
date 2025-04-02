#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits>

class Client {
private:
    std::string server_ip;
    int server_port;
    int sock;
    sockaddr_in server_address;

public:
    Client(const std::string& ip, int port) : server_ip(ip), server_port(port), sock(-1) {}

    bool createConnection() {
        // Crear el socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cerr << "Error al crear el socket." << std::endl;
            return false;
        }

        // Configurar la dirección del servidor
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(server_port);
        server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

        // Conectar al servidor
        if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
            std::cerr << "Error al conectar al servidor." << std::endl;
            close(sock);
            return false;
        }

        std::cout << "Conectado al servidor." << std::endl;
        return true;
    }
    
    std::string sendAndReceive(const std::string& message) {
        if (send(sock, message.c_str(), message.size(), 0) < 0) {
            std::cerr << "Error al enviar mensaje." << std::endl;
            return "";
        }

        char buffer[1024] = {0};
        int read_size = recv(sock, buffer, sizeof(buffer), 0);
        if (read_size > 0) {
            return std::string(buffer, read_size);
        }
        return "";
    }

    ~Client() {
        if (sock >= 0) {
            close(sock);
            std::cout << "Conexión cerrada." << std::endl;
        }
    }
};

#endif
