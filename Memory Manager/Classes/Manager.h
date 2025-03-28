// Manager.h
#ifndef MANAGER_H
#define MANAGER_H

#include "Bloque.h"
#include <vector> // will be used to organize memory positions.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Manager {
private:
    int actuallID = 2;
    void* memory_amount;
    void* last_address;
    vector<MemoryBlock> blks;    

    int Create(int size, string type) {

        if (blks.empty()){
            MemoryBlock memBlk;
            memBlk.frstPtr = memory_amount;
            memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + (size * sizeof(char)));
            memBlk.refCount = 0;
            memBlk.type = type;
            memBlk.id = 1;

            blks.push_back(memBlk);
            cout << "Create llamado con size: " << size << " y type: " << type << endl;
            printMemoryBlock(memBlk);
            return 1;
        }
        else {
            MemoryBlock memBlk;
            MemoryBlock lastAdded = blks.back();
            void* nextMemoryUSe = lastAdded.lastPtr;

            // Adding necesary data to new block
            memBlk.frstPtr = nextMemoryUSe;
            memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + (size * sizeof(int)));
            memBlk.refCount = 0;
            memBlk.id = actuallID;
            memBlk.type = type;
            actuallID++;

            blks.push_back(memBlk);
            cout << "Create llamado con size: " << size << " y type: " << type << endl;
            return memBlk.id;
        }
    }

    int Set(int id, std::string value) {
        for (size_t i = 0; i < blks.size(); i++) {
            if (blks[i].id == id) {
                void* ptr = blks[i].frstPtr;

                if (blks[i].type == "int") {
                    int intValue = std::stoi(value);
                    *static_cast<int*>(ptr) = intValue;
                }
                else if (blks[i].type == "float") {
                    float floatValue = std::stof(value);
                    *static_cast<float*>(ptr) = floatValue;
                }
                else if (blks[i].type == "string") {
                    *static_cast<std::string*>(ptr) = value;
                }
                else {
                    std::cerr << "Error: Tipo no soportado: " << blks[i].type << std::endl;
                    return -1;
                }

                return 0; // success
            }
        }

        return -1; // id not found
    }
    
    std::variant<int, float, std::string> Get(int id) {
        for (size_t i = 0; i < blks.size(); i++) {
            if (blks[i].id == id) {
                void* ptr = blks[i].frstPtr;
    
                if (blks[i].type == "int") {
                    int intValue = *(static_cast<int*>(ptr));
                    return intValue;  // Retorna el valor de tipo int
                }
                else if (blks[i].type == "float") {
                    float floatValue = *(static_cast<float*>(ptr));
                    return floatValue;  // Retorna el valor de tipo float
                }
                else if (blks[i].type == "string") {
                    std::string stringValue = *(static_cast<std::string*>(ptr));
                    return stringValue;  // Retorna el valor de tipo string
                }
            }
        }
        return -1;  // Si no se encuentra el ID, devuelve error
    }
    

    int IncreaseRefCount(int id) {
        for (size_t i = 0; i < blks.size(); i++) {
            if (blks[i].id == id) {
                blks[i].refCount = blks[i].refCount + 1;
                return blks[i].refCount;
            }
        }
        return -1;  // Si no se encuentra el ID, devuelve error
    }

    int DecreaseRefCount(int id) {
        for (size_t i = 0; i < blks.size(); i++) {
            if (blks[i].id == id) {
                if ( blks[i].refCount != 0)
                {
                    blks[i].refCount = blks[i].refCount - 1;
                    return blks[i].refCount;
                }

                return 0;
            }
        }
        return -1;  // Si no se encuentra el ID, devuelve error
    }


public:
    Manager (int amount) {
        memory_amount = malloc(amount);

        cout << "1st Adress: " << memory_amount << endl;

        last_address = (void*)((char*)memory_amount + (amount * sizeof(int)));        
        cout << "Last Adress: " << last_address << endl;
    }

    ~Manager (){
        free(memory_amount);
        cout << "I AM FREE..." << endl;
    }

    std::variant<int, float, std::string> ReceiveMessage(string message) { 
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

    void printMemoryBlock(const MemoryBlock& block) {
        cout << "First Pointer Address: " << block.frstPtr << endl;
        cout << "Last Pointer Address: " << block.lastPtr << endl;
        cout << "Reference Count: " << block.refCount << endl;
        cout << "Type: " << block.type << endl;
    }

};

#endif
