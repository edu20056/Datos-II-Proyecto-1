#include <iostream>
#include "Memory Manager/Classes/Manager.h"

void run() {
    Manager manager(10); // MB 

    manager.ReceiveMessage("Create(4,int)"); // id 1
    manager.ReceiveMessage("Set(1,2)");


    manager.ReceiveMessage("Create(5,int)"); // id 2
    manager.ReceiveMessage("Set(2,1)");

    manager.ReceiveMessage("Create(4,float)"); // id 3
    manager.ReceiveMessage("Set(3,1.0)");

    manager.ReceiveMessage("DecreaseRefCount(2)"); //se elimina 2

    manager.ReceiveMessage("Create(1,char)"); // id 4
    manager.ReceiveMessage("Set(4,a)");

    manager.ReceiveMessage("Create(3,float)"); // id 5
    manager.ReceiveMessage("Set(5,1.0)");

    manager.ReceiveMessage("Create(5,int)"); // id 6
    manager.ReceiveMessage("Set(6,27)");

    manager.ReceiveMessage("Create(4,int)"); 
    manager.ReceiveMessage("Set(1,2)");
}

int main(){
    run();
    return 0;
}