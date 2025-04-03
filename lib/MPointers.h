#ifndef MPOINTERS_H
#define MPOINTERS_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits>
#include <sstream>
#include <mutex>
#include <stdexcept>
#include <cxxabi.h>

template <typename T>
class MPointer {
private:
    static std::string server_ip;
    static int server_port;
    static int sock;
    static sockaddr_in server_address;
    static bool initialized;
    static std::mutex mtx;

    int id;

    MPointer(int block_id) : id(block_id) {}

    std::string convertToString(T value) {
        std::ostringstream oss;

        if constexpr (std::is_same<T, bool>::value) {
            oss << (value ? "true" : "false");
        }
        // Handle char conversion explicitly
        else if constexpr (std::is_same<T, char>::value) {
            oss << value;  // Output with single quotes for chars
        }
        // Handle double conversion explicitly
        else if constexpr (std::is_same<T, double>::value) {
            oss << value;
        }
        // Handle floating-point and integral types
        else {
            oss << value;
        }

        return oss.str();
    }

    static std::string sendAndReceive(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        
        if (sock < 0) {
            throw std::runtime_error("Not connected to server");
        }

        if (send(sock, message.c_str(), message.size(), 0) < 0) {
            throw std::runtime_error("Error sending message");
        }

        char buffer[1024] = {0};
        int read_size = recv(sock, buffer, sizeof(buffer), 0);
        if (read_size <= 0) {
            throw std::runtime_error("Error receiving response");
        }

        return std::string(buffer, read_size);
    }

public:
    MPointer() : id(-1) {}

    ~MPointer() {
        if (id != -1) {
            try {
                std::stringstream ss;
                ss << "exit";
                sendAndReceive(ss.str());
            } catch (...) {
                // Destructor shouldn't throw
            }
        }
    }

    static void Init(const std::string& ip = "127.0.0.1", int port = 5005) {
        std::lock_guard<std::mutex> lock(mtx);
        
        if (initialized) return;

        server_ip = ip;
        server_port = port;

        // Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            throw std::runtime_error("Error creating socket");
        }

        // Configure server address
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(server_port);
        server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

        // Connect to server
        if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
            close(sock);
            sock = -1;
            throw std::runtime_error("Error connecting to server");
        }

        initialized = true;
    }

    static MPointer<T> New() {
        if (!initialized) {
            throw std::runtime_error("MPointer not initialized. Call Init() first");
        }

        // Get the demangled type name
        int status = 0;
        char* demangled = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
        std::string typeName = (demangled != nullptr) ? demangled : typeid(T).name();
        free(demangled);

        std::string response = sendAndReceive("Create(" + std::to_string(sizeof(T)) + "," + typeName + ")");
        
        try {
            int new_id = std::stoi(response);
            return MPointer<T>(new_id);
        } catch (...) {
            throw std::runtime_error("Invalid response from server");
        }
    }

    int operator&() { return id; }

    T operator*() const {

        if (id == -1) {
            throw std::runtime_error("Dereferencing null MPointer");
        }

        std::string response = sendAndReceive("Get(" + std::to_string(id) + ")");

        T value;
        std::istringstream iss(response);
        iss >> value;
        return value;
    }

    MPointer& operator=(const MPointer& other) {
        if (this != &other) {

            sendAndReceive("IncreaseRefCount(" + std::to_string(other.id) + ")");
            id = other.id;
            
            /*
            if (id != -1) {
                sendAndReceive("DecreaseRefCount(" + std::to_string(other) + ")");
            }
                */
        }
        return *this;
    }

    void operator=(T value) {

        if (id == -1) {
            throw std::runtime_error("Assigning to null MPointer");
        }

        std::cout << "VALUE TO SET : " << convertToString(value) << '\n';

        sendAndReceive("Set(" + std::to_string(id) + "," + convertToString(value) + ")");
    }
};

// Initialize static members
template <typename T> std::string MPointer<T>::server_ip = "127.0.0.1";
template <typename T> int MPointer<T>::server_port = 5005;
template <typename T> int MPointer<T>::sock = -1;
template <typename T> sockaddr_in MPointer<T>::server_address;
template <typename T> bool MPointer<T>::initialized = false;
template <typename T> std::mutex MPointer<T>::mtx;

#endif // MPOINTERS_H