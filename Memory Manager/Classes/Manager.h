// Manager.h
#ifndef MANAGER_H
#define MANAGER_H

#include "Bloque.h"
#include <vector> // will be used to organize memory positions.

using namespace std;
using namespace MemoryManager;

class Manager {
private:
    int memory_amount;

public:
    Manager (int amount)
    {
        memory_amount = amount;
    }

};

#endif
