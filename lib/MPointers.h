#ifndef MPOINTERS_H
#define MPOINTERS_H

// Include necessary dependencies
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

// Template MPointers Class
template <typename T>
class MPointer {

    private:

        // Static Members Shared Across All MPointer Instances (Sockets-Related)
        static std::string server_ip; // IP address of the memory server
        static int server_port; // Port number of the memory server
        static int sock; // Socket file descriptor
        static sockaddr_in server_address; // Server address structure
        static bool initialized; // Flag to check if initialized
        static std::mutex mtx; // Mutex (mutual exclusion) for thread safety

        int id;  // Unique identifier for the memory block

        MPointer(int block_id) : id(block_id) {} // Private Constructor

        // String Convertion Based on T type
        std::string convertToString(T value) {
            std::ostringstream oss;

            if constexpr (std::is_same<T, bool>::value) {
                oss << (value ? "true" : "false");
            }
            else if constexpr (std::is_same<T, char>::value) {
                oss << value;
            }
            else if constexpr (std::is_same<T, double>::value) {
                oss << value;
            }
            else {
                oss << value;
            }

            return oss.str();
        }

        // Static Method to Send Requests to Memory Manager and Receive Response
        static std::string memoryManagerRequest(const std::string& request) {
            std::lock_guard<std::mutex> lock(mtx);
            
            if (sock < 0) {
                throw std::runtime_error("No Connection with Memory Manager");
            }

            if (send(sock, request.c_str(), request.size(), 0) < 0) {
                throw std::runtime_error("Error Sending Request");
            }

            // Receive Response
            char buffer[1024] = {0};
            int read_size = recv(sock, buffer, sizeof(buffer), 0);
            if (read_size <= 0) {
                throw std::runtime_error("Error receiving response");
            }

            return std::string(buffer, read_size);
        }
        
        // Private Method For Value Writting in Memory via SET request
        void setValue(T value) {

            memoryManagerRequest("Set(" + std::to_string(id) + "," + convertToString(value) + ")");
        }

        // Private Method For Data Retriving via GET request
        T getValue() const {

            if (id == -1) {
                throw std::runtime_error("Null MPointer");
            }

            // Request Value Acquisition from Memory
            std::string response = memoryManagerRequest("Get(" + std::to_string(id) + ")");

            // Convert Response to the Aappropriate Type
            T value;
            std::istringstream iss(response);
            iss >> value;
            return value;
        }

        class DereferenceData {  // Aid Class wih the Dereference Data Operations
            private:
                
                MPointer<T>* mptr; // Pointer to the Parent MPointer
            
            public:

                DereferenceData(MPointer<T>* ptr) : mptr(ptr) {}
            
                // Conversion to T (for reading) : Delegate to MPointer's getValue
                operator T() const { return mptr->getValue(); }

                // Assignment (for writing) : Delegate to MPointer's setValue                
                T operator=(T value) { mptr->setValue(value); return value; }
        };
    
    public:

        MPointer() : id(-1) {} // Default Constructor (Null MPointer)

        ~MPointer() {
            if (id != -1) { // When destroy if the MPointer was not Null, Reduce the Reference Count
                try {
                    memoryManagerRequest("DecreaseRefCount(" + std::to_string(id) + ")");

                } catch (...) {
                    // Destructor Shouldn't Throw
                }
            }
        }

        // Static Initialization Method to Connect to the Memory Manager
        static void Init(const std::string& ip = "127.0.0.1", int port = 5005) {
            std::lock_guard<std::mutex> lock(mtx);
            
            if (initialized) return; // Already initialized

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

        // Static Method to Create a New Block in Memory 
        static MPointer<T> New() {
            if (!initialized) {
                throw std::runtime_error("MPointer not initialized. Call Init() first");
            }

            // Get the Demangled Type Name
            int status = 0;
            char* demangled = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
            std::string typeName = (demangled != nullptr) ? demangled : typeid(T).name();
            free(demangled);

            // Request Memory Allocation
            std::string response = memoryManagerRequest("Create(" + std::to_string(sizeof(T)) + "," + typeName + ")");
            
            try {
                int new_id = std::stoi(response); // Gets MPointer's ID
                return MPointer<T>(new_id); // Return new MPointer with this ID
            } catch (...) {
                throw std::runtime_error("Invalid Response from CREAT request");
            }
        }

        int operator&() { return id; } // Address-of operator - Returns the Memory Block ID

        // Dereference operator - Returns DereferenceData of MPoiner
        DereferenceData operator*() { return DereferenceData(this); }

        // Special Case : Assignment operator for MPointer-to-MPointer Assignment
        MPointer& operator=(const MPointer& other) {
            if (this != &other && other.id != -1) {

                // Increase Reference Count on the Server
                memoryManagerRequest("IncreaseRefCount(" + std::to_string(other.id) + ")");
                id = other.id;
            }

            return *this;
        }
};

// Initialize Static Members
template <typename T> std::string MPointer<T>::server_ip = "127.0.0.1";
template <typename T> int MPointer<T>::server_port = 5005;
template <typename T> int MPointer<T>::sock = -1;
template <typename T> sockaddr_in MPointer<T>::server_address;
template <typename T> bool MPointer<T>::initialized = false;
template <typename T> std::mutex MPointer<T>::mtx;

#endif // MPOINTERS_H