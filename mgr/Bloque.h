#ifndef BLOQUE_H
#define BLOQUE_H

#include <variant>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct MemoryBlock{
    void* frstPtr;
    void* lastPtr; 
    int refCount;
    int id;
    string type;
    bool alreadyAssigned;
};


#endif