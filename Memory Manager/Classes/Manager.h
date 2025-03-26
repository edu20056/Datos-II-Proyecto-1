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
using namespace MemoryManager;

class Manager {
private:
    void* memory_amount;
    void* last_address;
    vector<MemoryBlock> blks;    

    void Create(int size, string type) {

        if (blks.empty()){
            MemoryBlock memBlk;
            memBlk.frstPtr = memory_amount;
            memBlk.lastPtr = (void*)((char*)memBlk.frstPtr + (size * sizeof(int)));

            blks.push_back(memBlk);
            cout << "Create llamado con size: " << size << " y type: " << type << endl;
            printMemoryBlock(memBlk);
        }
    }

    void Set(int id, string value) {
        cout << "Set llamado con id: " << id << " y value: " << value << endl;
    }

    void Get(int id) {
        cout << "Get llamado con id: " << id << endl;
    }

    void IncreaseRefCount(int id) {
        cout << "IncreaseRefCount llamado con id: " << id << endl;
    }

    void DecreaseRefCount(int id) {
        cout << "DecreaseRefCount llamado con id: " << id << endl;
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

    int ReceiveMessage(string message) { // esta funcion deber retornar un numero que sea la direccion en caso de ser necesario.
        stringstream ss(message);
        string command;
        getline(ss, command, '(');

        if (command == "Create") {
            int size;
            string type;
            ss >> size;
            ss.ignore(1); // Ignorar la coma
            getline(ss, type, ')');
            Create(size, type);
            return 1;

        } else if (command == "Set") {
            int id;
            string value;
            ss >> id;
            ss.ignore(1); // Ignorar la coma
            getline(ss, value, ')');
            Set(id, value);
            return 2;

        } else if (command == "Get") {
            int id;
            ss >> id;
            Get(id);
            return 3;

        } else if (command == "IncreaseRefCount") {
            int id;
            ss >> id;
            IncreaseRefCount(id);
            return 4;

        } else if (command == "DecreaseRefCount") {
            int id;
            ss >> id;
            DecreaseRefCount(id);
            return 5;
            
        return 0;
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
