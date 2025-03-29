#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <thread>
#include <variant>
#include "Bloque.h"
#include "Manager.h"

void RunGarbageCollector(Manager& Manager)
{
    while (true)
    {
        Manager.GarbageCollector();
        std::this_thread::sleep_for(std::chrono::seconds(10)); 
    }
}

void handle_client(int client_socket, int client_number, Manager manager) {
    char buffer[1024] = {0};
    int read_size;
    
    std::thread garbageCollectorThread(RunGarbageCollector, std::ref(manager));
    garbageCollectorThread.detach(); 
    // Bucle para recibir y responder mensajes
    while ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        std::cout << "Mensaje recibido de Cliente " << client_number << ": " 
                  << buffer << std::endl;
        
        // Enviar mensaje a manager y recibir respuesta
        std::variant<int, float, std::string, char, bool, double> respuesta_manager = manager.ReceiveMessage(buffer);

        std::string respuesta_str = std::visit([](auto&& arg) -> std::string {
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                // Si el tipo es std::string, simplemente devolvemos el valor como está
                return arg;
            }
            else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, char>) {
                // Si el tipo es char, verificamos si es un carácter ASCII imprimible
                if (std::isprint(arg)) {
                    return std::string(1, arg);  // Convertir el char a un string
                } else {
                    return "[Non-printable ASCII]";  // Si no es imprimible
                }
            }
            else {
                // Para otros tipos numéricos, usamos std::to_string
                return std::to_string(arg);
            }
        }, respuesta_manager);
        

        // Responder al cliente con un mensaje de confirmación
        std::string response = "Recibimos tu mensaje, Cliente " + std::to_string(client_number) + ". Esta respuesta es: " + respuesta_str;
        send(client_socket, response.c_str(), response.length(), 0);

        // Limpiar el buffer para el próximo mensaje
        memset(buffer, 0, sizeof(buffer));
    }

    if (read_size == 0) {
        std::cout << "El Cliente " << client_number << " se desconectó." << std::endl;
    } else if (read_size == -1) {
        std::cerr << "Error al recibir mensaje." << std::endl;
    }

    // Cerrar la conexión con el cliente
    close(client_socket);
}

int main() {
    std::string folder;
    int server_port, additional_num;
    std::string server_ip = "127.0.0.1";  // IP local para el servidor

    std::cout << "Ingresa el puerto del servidor: ";
    std::cin >> server_port;
    std::cout << "Ingresa la cantidad de MB por reservar: ";
    std::cin >> additional_num;
    std::cout << "Ingresa la carpeta del servidor: ";
    std::cin >> folder;

    // Crear Ojeto manager para Memory Manager
    Manager manager(additional_num);

    // Crear el socket del servidor
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error al crear el socket." << std::endl;
        return -1;
    }

    // Configurar la dirección del servidor
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

    // Hacer bind del socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error al hacer bind." << std::endl;
        close(server_socket);
        return -1;
    }

    // Escuchar conexiones entrantes
    if (listen(server_socket, 3) < 0) {
        std::cerr << "Error al escuchar." << std::endl;
        close(server_socket);
        return -1;
    }

    std::cout << "Servidor en espera de conexiones..." << std::endl;

    int client_counter = 1;

    while (true) {
        sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);
        if (client_socket < 0) {
            std::cerr << "Error al aceptar la conexión." << std::endl;
            continue;
        }

        std::cout << "Cliente " << client_counter << " conectado desde: " 
                  << inet_ntoa(client_address.sin_addr) << ":" 
                  << ntohs(client_address.sin_port) << std::endl;

        // Crear un hilo para manejar al cliente
        std::thread client_thread(handle_client, client_socket, client_counter, manager);
        client_thread.detach();  // Desprender el hilo para que se ejecute independientemente

        client_counter++;
    }

    // Cerrar el socket del servidor
    close(server_socket);
    return 0;
}