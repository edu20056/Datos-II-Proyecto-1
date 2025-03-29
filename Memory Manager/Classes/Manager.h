// Manager.h
#ifndef MANAGER_H
#define MANAGER_H

#include "Bloque.h"
#include <vector> // will be used to organize memory positions.
#include <type_traits> // used for detecting strings
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <thread>  // Required for sleep_for
#include <chrono>  // Required for milliseconds

#include <filesystem>     // File && Directory Operations
#include <fstream>        // File Writting

using namespace std;

class Manager {

    private:

        int actuallID = 2;
        void* memory_amount;
        void* last_address;
        vector<MemoryBlock> blks; 

        std::string dumpDir;
        
        std::string generateTimestamp() {

            // System Time
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            
            // Create string stream for timestamp
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S_");
            
            // Add milliseconds
            auto duration = now.time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
            ss << std::setfill('0') << std::setw(3) << millis.count() << ".dump";
            
            return ss.str();
        }

        void dumpFileReport(std::string input) {

            // Creates Dump Folder
            if (!std::filesystem::exists(dumpDir)) {
                std::filesystem::create_directories(dumpDir);
            }
        
            // Generates File with TimeStamp as name
            std::string filename = dumpDir + "/" + generateTimestamp();
            std::ofstream dumpFile(filename);
        
            // Write memory information
            dumpFile << "\n========== MEMORY MANAGER REPORT ==========\n";
            dumpFile << "Memory Start Address : " << memory_amount << " bytes\n";
            dumpFile << "Last Address : " << last_address << " bytes\n";
            dumpFile << "Total Memory Size : " << 
                (char*)last_address - (char*)memory_amount << " bytes\n";
            dumpFile << "-------------------------------------------\n\n";

            dumpFile << "-------------------------------------------\n";
            for (const MemoryBlock block : blks) {
                dumpFile << "ID : " << block.id << '\n';
                dumpFile << "  - First Address : " << block.frstPtr << '\n';
                dumpFile << "  - Last Address : " << block.lastPtr << '\n';
                dumpFile << "  - Size : " << (char*)block.lastPtr - (char*)block.frstPtr << '\n';
                dumpFile << "  - Type : " << block.type << '\n';
                dumpFile << "  - Ref Count : " << block.refCount << '\n';
                dumpFile << "-------------------------------------------\n\n";
            }

            dumpFile << "---------- Operation Details -----------\n";
            dumpFile << input << '\n';
            dumpFile.close();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

    public:

        Manager (int amount, std::string dir = "./Dump Folder") {
            memory_amount = malloc(amount);

            cout << "1st Adress: " << memory_amount << endl;
            last_address = (void*)((char*)memory_amount + (amount * sizeof(int)));        
            cout << "Last Adress: " << last_address << endl;

            dumpDir = dir;
        }

        ~Manager (){
            free(memory_amount);
            cout << "I AM FREE..." << endl;
        }

        int Create(int size, string type) { 

            if (blks.empty()){
                MemoryBlock memBlk;
                memBlk.frstPtr = memory_amount;
                memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + (size * sizeof(char)));
                memBlk.refCount = 0;
                memBlk.type = type;
                memBlk.id = 1;
                memBlk.alreadyAssigned = false;

                blks.push_back(memBlk);

                std::stringstream ss;
                ss << "Create(" << size << ", " << type << ")\n";
                dumpFileReport(ss.str());

                return 1; 
            }
            else {
                MemoryBlock memBlk;
                MemoryBlock lastAdded = blks.back();
                void* nextMemoryUSe = lastAdded.lastPtr;

                void* endOfAllocation = (char*)nextMemoryUSe + size;

                if (endOfAllocation > last_address)
                {
                    return -2; //Espacio de nueva varible excede bloque de memoria de Manager.
                }

                // Adding necesary data to new block
                memBlk.frstPtr = nextMemoryUSe;
                memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + (size * sizeof(int)));
                memBlk.refCount = 0;
                memBlk.id = actuallID;
                memBlk.type = type;
                memBlk.alreadyAssigned = false;
                actuallID++;

                blks.push_back(memBlk);

                std::stringstream ss;
                ss << "Create(" << size << ", " << type << ")\n";
                dumpFileReport(ss.str());

                return memBlk.id;
            }
        }

        int Set(int id, std::string value) {
            cout << "Set llamado con id: " << id << " y value: " << value << endl;
        
            for (size_t i = 0; i < blks.size(); i++) {
                if (blks[i].id == id) {
                    void* ptr = blks[i].frstPtr;
                    void* ptrLast = blks[i].lastPtr;
                    
                    // Calculamos el tamaño del bloque de memoria disponible
                    size_t blockSize = static_cast<char*>(ptrLast) - static_cast<char*>(ptr);
                    
                    if (blks[i].type == "int") {
                        // Tamaño de un int
                        size_t sizeRequired = sizeof(int);
                        if (sizeRequired > blockSize) {
                            std::cerr << "Error: Tamaño insuficiente para el tipo int" << std::endl;
                            return -3; // Error de tamaño insuficiente
                        }
                        int intValue = std::stoi(value);
                        *static_cast<int*>(ptr) = intValue;
                    }
                    else if (blks[i].type == "float") {
                        // Tamaño de un float
                        size_t sizeRequired = sizeof(float);
                        if (sizeRequired > blockSize) {
                            std::cerr << "Error: Tamaño insuficiente para el tipo float" << std::endl;
                            return -3; // Error de tamaño insuficiente
                        }
                        float floatValue = std::stof(value);
                        *static_cast<float*>(ptr) = floatValue;
                    }
                    else if (blks[i].type == "double") {
                        // Tamaño de un double
                        size_t sizeRequired = sizeof(double);
                        if (sizeRequired > blockSize) {
                            std::cerr << "Error: Tamaño insuficiente para el tipo double" << std::endl;
                            return -3; // Error de tamaño insuficiente
                        }
                        double doubleValue = std::stod(value);
                        *static_cast<double*>(ptr) = doubleValue;
                    }

                    else if (blks[i].type == "string") {
                        size_t sizeRequired = value.length() + 1; // +1 for string finished in 0
                        std::string* strPtr = static_cast<std::string*>(ptr);
                        if (sizeRequired > blockSize) {
                            std::cerr << "Error: Tamaño insuficiente para el tipo string" << std::endl;
                            return -3;
                        }
                        std::cout << "VALOR: " << value << std::endl;

                        //Conversion to avoid errors
                        std::string convertedValue = value;
                        
                        // Verify time compilation
                        if (!std::is_same<std::string, decltype(*static_cast<std::string*>(ptr))>::value) {
                            std::cerr << "Error: El puntero no apunta a un std::string válido." << std::endl;
                            return -4;
                        }

                        // Asignation
                        *static_cast<std::string*>(ptr) = convertedValue;
                    }

                    
                    else if (blks[i].type == "char") {
                        // Tamaño de un char
                        size_t sizeRequired = sizeof(char);
                        if (sizeRequired > blockSize) {
                            std::cerr << "Error: Tamaño insuficiente para el tipo char" << std::endl;
                            return -3; // Error de tamaño insuficiente
                        }
                        if (value.length() == 1) {
                            *static_cast<char*>(ptr) = value[0]; 
                        } else {
                            std::cerr << "Error: No se puede convertir a char (longitud > 1)" << std::endl;
                            return -2; // Error si longitud de char > 1
                        }
                    }
                    else if (blks[i].type == "bool") {
                        // Tamaño de un bool
                        size_t sizeRequired = sizeof(bool);
                        if (sizeRequired > blockSize) {
                            std::cerr << "Error: Tamaño insuficiente para el tipo bool" << std::endl;
                            return -3; // Error de tamaño insuficiente
                        }
                        if (value == "true") {
                            *static_cast<bool*>(ptr) = true;
                        } 
                        else if (value == "false") {
                            *static_cast<bool*>(ptr) = false;
                        } 
                        else {
                            std::cerr << "Error: Valor inválido para tipo bool: " << value << std::endl;
                            return -1; // Retorna error si el valor no es "true" o "false"
                        }
                    }
                    else {
                        std::cerr << "Error: Tipo no soportado: " << blks[i].type << std::endl;
                        return -1;
                    }
        
                    IncreaseRefCount(id);
                    blks[i].alreadyAssigned = true;

                    std::stringstream ss;
                    ss << "Set(" << id << ")\n";
                    dumpFileReport(ss.str());

                    return 0; // success
                }
            }
        
            return -1; // id not found
        }    
        
        std::variant<int, float, std::string, char, bool, double> Get(int id) {
            for (size_t i = 0; i < blks.size(); i++) {
                if (blks[i].id == id) {
                    void* ptr = blks[i].frstPtr;
        
                    if (blks[i].type == "int") {
                        return *(static_cast<int*>(ptr));
                    }
                    else if (blks[i].type == "float") {
                        return *(static_cast<float*>(ptr));
                    }
                    else if (blks[i].type == "double") {
                        return *(static_cast<double*>(ptr));
                    }
                    else if (blks[i].type == "char") {
                        return *(static_cast<char*>(ptr));
                    }
                    else if (blks[i].type == "bool") {
                        return *(static_cast<bool*>(ptr));
                    }
                    else if (blks[i].type == "string") {
                        return *(static_cast<std::string*>(ptr));
                    }
                }
            }
            return -1;  // Devuelve -1 si no se encuentra el ID
        }

        int IncreaseRefCount(int id) {
            cout << "Se llamo increase con id: "<< id << endl;
            for (size_t i = 0; i < blks.size(); i++) {
                if (blks[i].id == id) {
                    blks[i].refCount = blks[i].refCount + 1;

                    std::stringstream ss;
                    ss << "IncreaseRefCount(" << id << ")\n";
                    dumpFileReport(ss.str());

                    return blks[i].refCount;
                }
            }
            return -1;  // Si no se encuentra el ID, devuelve error
        }

        int DecreaseRefCount(int id) {
            cout << "Se llamo decrease con id: "<< id << endl;
            for (size_t i = 0; i < blks.size(); i++) {
                if (blks[i].id == id) {
                    if ( blks[i].refCount > 0)
                    {
                        blks[i].refCount = blks[i].refCount - 1;

                        std::stringstream ss;
                        ss << "DecreaseRefCount(" << id << ")\n";
                        dumpFileReport(ss.str());

                        return blks[i].refCount;
                    }

                    return 0; //Referencias menores que 1,
                }
            }
            return -1;  // Si no se encuentra el ID, devuelve error
        }

        std::variant<int, float, std::string, char, bool, double> ReceiveMessage(string message) { 
            stringstream ss(message);
            string command;
            getline(ss, command, '(');

            if (command == "Create") {
                int size;
                string type;
                ss >> size;
                ss.ignore(1); // Ignorar la coma
                getline(ss, type, ')');
                return Create(size, type);

            } else if (command == "Set") {
                int id;
                string value;
                ss >> id;
                ss.ignore(1); // Ignorar la coma
                getline(ss, value, ')');
                return Set(id, value);

            } else if (command == "Get") {
                int id;
                ss >> id;
                return Get(id);

            } else if (command == "IncreaseRefCount") {
                int id;
                ss >> id;
                return IncreaseRefCount(id);

            } else if (command == "DecreaseRefCount") {
                int id;
                ss >> id;
                return DecreaseRefCount(id);
            }

            else {
                return -1; //Error
            }
        }

        bool GarbageCollector () // Boolean para que si es true cree un DumpFile
        {
            bool changes = false;
            cout << "Size de vector: " << blks.size() << endl;
            for (size_t i = blks.size(); i-- > 0; ) { // Recorrer de atrás hacia adelante
                cout << "Bool de: " << blks[i].id << " Es: " << blks[i].alreadyAssigned << endl;
                if (blks[i].alreadyAssigned && blks[i].refCount <= 0) {
                    cout << "Se está borrando el id: " << blks[i].id << endl;
                    blks.erase(blks.begin() + i);
                    changes = true;

                    std::stringstream ss;
                    ss << "Garbage Collector Made Some Changes...\n";
                    dumpFileReport(ss.str());
                }
            }
            cout << "Estado de recolector de basura: "<< changes << endl;
            return changes;
        }

        void MemoryDefragmentation() {

            /* pseudo code...
            void* lastAddress = memoryBlock; 
            for (MemoryBlock* blk : allocatedMemory) {
                blk->frstPtr= lastAddress;
                blk->lastPtr= (void*)((char*)blk->frstPtr + blk->size - 1);
                lastAddress = blk->lastPtr + 1;
            }
            */

            std::stringstream ss;
            ss << "Memory Defragmentation...\n";
            dumpFileReport(ss.str());
        }
};

#endif
