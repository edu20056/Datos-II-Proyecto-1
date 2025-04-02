#include <iostream>
#include "Memory Manager/Classes/Manager.h"

void run() {
    Manager manager(26); // MB 

    manager.ReceiveMessage("Create(4,int)"); // id 1
    manager.ReceiveMessage("Set(1,2)");



}

int main(){
    run();
    return 0;
}