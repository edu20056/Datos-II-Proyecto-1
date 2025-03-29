#include <iostream>
#include "Memory Manager/Classes/Manager.h"

void run() {
    Manager manager(20);

    manager.ReceiveMessage("Create(4,int)"); 
    manager.ReceiveMessage("Set(1,2)");
}

int main(){
    run();
    return 0;
}