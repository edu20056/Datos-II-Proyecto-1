#include <variant>
#include <string>
#include <iostream>
#include <vector>

#ifndef BLOQUE_H
#define BLOQUE_H

using namespace std;

struct MemoryBlock{
    void* frstPtr;
    void* lastPtr; 
    int refCount;
    string type;
};

namespace MemoryManager{

    class Bloque {
    private:
        string data_type;
        int references; 
        int memory_ubi;
        variant<int, float, string> data;

    public:

        Bloque(string type, int mem_ubi, variant<int, float, string>  new_data, int ref) {
            data_type = type;
            memory_ubi = mem_ubi;
            data = new_data;
            references = ref;

            if (data_type == "int") {
                data = 0;
            } else if (data_type == "float") {
                data = 0.0f;
            } else if (data_type == "string") {
                data = "";
            }
        }

        void mostrarData() {
            cout << "Tipo de dato: " << data_type << "\nReferencias: " << references
                << "\nUbicación de memoria: " << memory_ubi << endl;

            if (data_type == "int") {
                cout << "Data (int): " << get<int>(data) << endl;
            } else if (data_type == "float") {
                cout << "Data (float): " << get<float>(data) << endl;
            } else if (data_type == "string") {
                cout << "Data (string): " << get<string>(data) << endl;
            }
        }
    };
}

#endif