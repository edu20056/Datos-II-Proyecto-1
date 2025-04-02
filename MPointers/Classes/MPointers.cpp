#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits> // Necesario para std::numeric_limits

template<typename T>
class MPointer {
    
    private:

        int sock; 
        static bool connection; 
        
        int id; // ID Of the Memory Block in the Memory

        void memoryManagerRequest(std::string request) {

            // Connection Status Check
            if (!connection) {
                throw std::runtime_error("!ERROR : No Connection with Memory Manager ... (╯’□’)╯\n");
            }

            // Send Message to Memory Manager
            if (send(sock, request.c_str(), request.size(), 0) < 0) {
                std::cerr << "!ERROR : At Message Sending ... ◝(^⌣^)◜\n";
            }
        }
    
    public:

        MPointer() : id(-1) {}  // Default constructor with invalid ID

        ~MPointer() {
            static
            // Request Formatting
            std::stringstream ss;
            ss << "DecreaseRefCount(" << id << ")";

            memoryManagerRequest(ss.str()); // Send Request

            // Close Socket
            if (connection) {
                close(sock);
                connection = false;
            }
        }

        static void Init(int port) {

            if(connection) return; // Check Initialzed Status

            // Clean Buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Init z" << "\n";

            // Initialize Socket
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0) {
                std::cerr << "!ERROR : At Initializing Socket ... (╥﹏╥)\n";
            }
            
            std::cout << "Init A" << "\n";
            
            // Server Direction Config
            sockaddr_in server_address;
            std::string server_ip = "127.0.0.1";
            server_address.sin_family = AF_INET;
            server_address.sin_port = htons(port);
            server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

            std::cout << "Init B" << "\n";

            // Binding with Server
            if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
                std::cerr << "!ERROR : On Binding with Server ... (✖﹏✖)\n";
                close(sock);
            }

            connection = true; // Change Connection Status
            std::cout << "✓ Conectado al servidor en el puerto " << port << "\n";
        }

        MPointer<T>& New() {

            // Check Initialzed Status
            if(!connection) {
                throw std::runtime_error("!ERROR : MPointer not initialized ... ( ⊙︿⊙ )\n");
            }

            // Request Formatting
            std::stringstream ss;
            ss << "Create(" << sizeof(T) << "," << typeid(T).name() << ")";

            memoryManagerRequest(ss.str()); // Send Request

            // Memory Manager Answer
            char buffer[1024] = {0};
            int read_size = recv(sock, buffer, sizeof(buffer), 0);
            
            if(read_size > 0) {
                id = std::stoi(buffer);
            } else { std::cout << "!ERROR : " << buffer; }

            return *this;
        }

        void operator*=(const T& value) {

            // Request Formatting
            std::stringstream ss;
            ss << "Set(" << id << "," << value << ")";

            memoryManagerRequest(ss.str()); // Send Request
        }

        T operator*() {

            // Request Formatting
            std::stringstream ss;
            ss << "Get(" << id << ")";

            memoryManagerRequest(ss.str()); // Send Request

            // Recibir la respuesta del servidor
            char buffer[1024] = {0};
            int read_size = recv(sock, buffer, sizeof(buffer), 0);
            
            if(read_size < 0) {
                throw std::runtime_error("!ERROR : Receiving Value");
            }

            // Recive && Return Value
            T value;
            std::istringstream iss(buffer);
            iss >> value;
            return value;
        }

        int operator&() { return id; } // Return Id

        MPointer& operator=(const MPointer& mptr) {

            if(this != mptr) {
                id =  &mptr; // Operator Reassignment
            }

            // Request Formatting
            std::stringstream ss;
            ss << "IncreaseRefCount(" << &mptr << ")";

            memoryManagerRequest(ss.str()); // Send Request

            return *this;
        }
};


// Initialize Static Members
template<typename T> bool MPointer<T>::connection = false;