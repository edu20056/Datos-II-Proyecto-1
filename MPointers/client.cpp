#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    std::string server_ip = "127.0.0.1";  // IP local para el servidor
    int server_port;

    std::cout << "Ingresa el puerto del servidor: ";
    std::cin >> server_port;

    // Crear el socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error al crear el socket." << std::endl;
        return -1;
    }

    // Configurar la dirección del servidor
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error al conectar al servidor." << std::endl;
        close(sock);
        return -1;
    }

    std::cout << "Conectado al servidor." << std::endl;

    // Bucle para enviar mensajes
    std::string message;
    while (true) {
        std::cout << "Escribe un mensaje (o 'exit' para salir): ";
        std::cin.ignore();  // Limpiar el buffer
        std::getline(std::cin, message);

        if (message == "exit") {
            break;  // Salir del bucle si el mensaje es 'exit'
        }

        // Enviar mensaje al servidor
        if (send(sock, message.c_str(), message.size(), 0) < 0) {
            std::cerr << "Error al enviar mensaje." << std::endl;
            break;
        }

        // Recibir la respuesta del servidor
        char buffer[1024] = {0};
        int read_size = recv(sock, buffer, sizeof(buffer), 0);
        if (read_size > 0) {
            std::cout << "Respuesta del servidor: " << buffer << std::endl;
        }
    }

    // Cerrar el socket
    close(sock);
    std::cout << "Conexión cerrada." << std::endl;
    return 0;
}
