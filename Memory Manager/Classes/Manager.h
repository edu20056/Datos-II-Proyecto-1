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
#include <array>
#include <thread>  // Required for sleep_for
#include <chrono>  // Required for milliseconds

#include <filesystem>     // File && Directory Operations
#include <fstream>        // File Writting

using namespace std;

class Manager {

    private:

        int currentId;
        void* memory_amount;
        void* last_address;
        vector<MemoryBlock> blks; 
        vector<std::array<void*, 2>> freeSpace; // it is a vector of arrays, they contain pointers like this 
        //[0x1,0x4] meaning that the space is free in that location
    

        std::string dumpDir;

        std::string readableGetMethod(std::variant<int, float, char, bool, double> value) {
            if (std::holds_alternative<int>(value)) {
                return std::to_string(std::get<int>(value));
            } 
            if (std::holds_alternative<float>(value)) {
                return std::to_string(std::get<float>(value));
            } 
            if (std::holds_alternative<double>(value)) {
                return std::to_string(std::get<double>(value));
            } 
            if (std::holds_alternative<char>(value)) {
                return std::string(1, std::get<char>(value));
            } 
            if (std::holds_alternative<bool>(value)) {
                return std::get<bool>(value) ? "true" : "false";
            }
            
            return "ID's value not found...";
        }
        
        std::string generateTimestamp(const bool& flag) {

            // System Time
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            
            // Create string stream for timestamp
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), 
                flag ? "%Y%m%d_%H%M%S_" : "%m/%d/%Y %H:%M:%S ");
            
            // Add milliseconds
            auto duration = now.time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
            ss << std::setfill('0') << std::setw(3) << millis.count() << (flag ? ".dump" : " -> ");
            
            return ss.str();
        }

        void dumpFileReport(std::string input) {

            // Creates Dump Folder
            if (!std::filesystem::exists(dumpDir)) {
                std::filesystem::create_directories(dumpDir);
            }
        
            // Generates File with TimeStamp as name
            std::string filename = dumpDir + "/" + generateTimestamp(true);
            std::ofstream dumpFile(filename);

            size_t usedMemorySize = 0;
            for (const MemoryBlock& block : blks) {
                usedMemorySize += (char*)block.lastPtr - (char*)block.frstPtr;
            }

            double usagePorcentaje = static_cast<double>
                (usedMemorySize) / ((char*)last_address - (char*)memory_amount) * 100;
        
            // Write memory information
            dumpFile << "\n========== MEMORY MANAGER REPORT ==========\n";
            dumpFile << "Memory Start Address : " << memory_amount << " bytes\n";
            dumpFile << "Last Address : " << last_address << " bytes\n";
            dumpFile << "Total Memory Size : " << 
                (char*)last_address - (char*)memory_amount << " bytes\n";
            dumpFile << "Allocated Memory : " << usedMemorySize << " bytes (" << usagePorcentaje << "%) \n";
            dumpFile << "-------------------------------------------\n\n";

            for (const MemoryBlock block : blks) {
                dumpFile << "ID : " << block.id << 
                    " ---------------------------- [ " << readableGetMethod(Get(block.id)) << " ]\n";
                dumpFile << "  - First Address : " << block.frstPtr << '\n';
                dumpFile << "  - Last Address : " << block.lastPtr << '\n';
                dumpFile << "  - Size : " << (char*)block.lastPtr - (char*)block.frstPtr << '\n';
                dumpFile << "  - Type : " << block.type << '\n';
                dumpFile << "  - Ref Count : " << block.refCount << '\n';
                dumpFile << "-------------------------------------------\n\n";
            }

            dumpFile << "---------- Operation Details -----------\n";
            dumpFile << generateTimestamp(false); 
            dumpFile << input << '\n';
            dumpFile.close();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        void dumpFolderReset() {

            try {

                if (std::filesystem::exists(dumpDir) && std::filesystem::is_directory(dumpDir)) {

                    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

                    // Iterate through all the files and directories within the folder
                    std::filesystem::remove_all(dumpDir); 

                    // Finally, remove the directory itself
                    std::filesystem::remove(dumpDir);
                }

            } catch (const std::filesystem::filesystem_error& e) {

                std::cerr << "Error while deleting directory: " << e.what() << '\n';
            }
        }

    public:

        Manager (int amount, std::string dir = "./Dump Folder") {
            memory_amount = malloc(amount);

            currentId = 2;

            cout << "1st Adress: " << memory_amount << endl;
            last_address = (void*)((char*)memory_amount + amount);       
            cout << "Last Adress: " << last_address << endl;

            dumpDir = dir;
            dumpFolderReset();
            dumpFileReport("<Memory Initialized>");
        }

        ~Manager (){
            free(memory_amount);
            cout << "I AM FREE..." << endl;
        }

        int getHighestLastPtrID(const std::vector<MemoryBlock>& blks) { // Looks for the largest distanced element from the origin, so in case there are no
            // Empty spaces between blocks just takes lasptr from this ids block
            int highestID = blks[0].id;
            void* highestLastPtr = blks[0].lastPtr;
        
            for (const auto& block : blks) {
                if (block.lastPtr > highestLastPtr) {
                    highestLastPtr = block.lastPtr;
                    highestID = block.id;
                }
            }
            
            return highestID;
        }

        int findSufficientSpace(int size) {
            if (freeSpace.size() == 0)
            {
                return -1;
            }
            for (size_t i = 0; i < freeSpace.size(); ++i) {
                void* ptr1 = freeSpace[i][0];
                void* ptr2 = freeSpace[i][1];
        
                size_t byteDifference = static_cast<char*>(ptr2) - static_cast<char*>(ptr1);
                if (byteDifference >= size) {
                    return i; // Retorna el índice del bloque adecuado
                }
            }
            return -1; // Retorna -1 si no hay un bloque con suficiente espacio
        }

        int Create(int size, string type) { 

            // Verifica si la lista de bloques está vacía
            if (blks.empty()){
                MemoryBlock memBlk;
                memBlk.frstPtr = memory_amount; // Primer bloque comienza en la cantidad de memoria disponible
                memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + (size)); // Agrega tamaño en bytes, no sizeof(char) ya que size es en bytes
                memBlk.refCount = 0;
                memBlk.type = type;
                memBlk.id = 1;
                memBlk.alreadyAssigned = false;
        
                blks.push_back(memBlk); // Agrega el primer bloque a la lista
        
                std::stringstream ss;
                ss << "Create(" << size << ", " << type << ")\n";
                dumpFileReport(ss.str()); // Imprime el informe
        
                return 1; 
            }
            else {
                int indexSpace = findSufficientSpace(size); 
                if ( indexSpace < 0){
                    cout << "CASITO -1" << endl;
                    MemoryBlock memBlk;
                    MemoryBlock lastAdded;
                    int largeID = getHighestLastPtrID(blks);
                    for (int i = 0; i < blks.size(); i++){
                        if (blks[i].id == largeID){
                            lastAdded = blks[i];
                            break;
                        }

                    }
                    
                    void* nextMemoryUse = static_cast<char*>(lastAdded.lastPtr);// La siguiente memoria empieza donde termina el último bloque
            
                    // Calcula la dirección final del nuevo bloque de memoria
                    void* endOfAllocation = (char*)nextMemoryUse + size;
            
                    if (endOfAllocation > last_address)
                    {
                        return -2; // not enough space
                    }
            
                    // New memory block configuration
                    memBlk.frstPtr = nextMemoryUse; 
                    memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + size); 
                    memBlk.refCount = 0;
                    memBlk.id = actuallID;
                    memBlk.type = type;
                    memBlk.alreadyAssigned = false;
                    actuallID++;
            
                    blks.push_back(memBlk); // Add block to list
            
                    std::stringstream ss;
                    ss << "Create(" << size << ", " << type << ")\n";
                    dumpFileReport(ss.str()); 
            
                    return memBlk.id;
                }
                else{
                    cout << "CASITO x con size: " << size<< endl;
                    MemoryBlock memBlk;
                    memBlk.frstPtr = static_cast<char*>(freeSpace[indexSpace][0]);
                    memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + size); 
                    memBlk.id = actuallID;
                    memBlk.refCount = 0;
                    memBlk.type = type;
                    memBlk.alreadyAssigned = false;
                    actuallID++;
                    
                    if ((char*)freeSpace[indexSpace][1] - (char*)freeSpace[indexSpace][0] == size) //if new blocks size is equals to freeSpace[i] space
                    {
                        freeSpace.erase(freeSpace.begin() + indexSpace);
                        blks.push_back(memBlk); // Add block to list

                    }

                    else{

                        blks.push_back(memBlk); // Add block to list

                        void* newFirstPtr = static_cast<char*>(freeSpace[indexSpace][0]) + size;
                        freeSpace[indexSpace][0] = newFirstPtr;
                        
                        // Calcular bytes restantes
                        size_t remainingBytes = static_cast<char*>(freeSpace[indexSpace][1]) - static_cast<char*>(freeSpace[indexSpace][0]);
                        // Mostrar en consola
                        std::cout << "Bytes restantes en el bloque: " << remainingBytes << " bytes" << std::endl;


                    }

                    std::cout << "Espacios en freeSpace: " << freeSpace.size() << " bytes" << std::endl;

                    std::stringstream ss;
                    ss << "Create(" << size << ", " << type << ")\n";
                    dumpFileReport(ss.str()); 
            
                    return memBlk.id;

                }

            }
        }
        
        int Set(int id, std::string value) {
        
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

                    cout << "Set llamado con id: " << id << " y value: " << value << endl;
        
                    IncreaseRefCount(id);
                    blks[i].alreadyAssigned = true;

                    std::stringstream ss;
                    ss << "Set(" << id << ", " << value << ")\n";
                    dumpFileReport(ss.str());

                    return 0; // success
                }
            }
        
            return -1; // id not found
        }    
        
        std::variant<int, float, char, bool, double> Get(int id) {
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

                        GarbageCollector();
                        return blks[i].refCount;
                    }
                    return 0; //Referencias menores que 1,
                }
            }
            return -1;  // Si no se encuentra el ID, devuelve error
        }

        std::variant<int, float, char, bool, double> ReceiveMessage(string message) { 
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

                    // Creates references for empty space
                    void* ptr1 = blks[i].frstPtr;
                    void* ptr2 = blks[i].lastPtr;
                    std::array<void*, 2> newEntry = {ptr1, ptr2};
                    freeSpace.push_back(newEntry);
                    
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

};

#endif
