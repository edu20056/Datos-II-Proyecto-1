#include <iostream>
#include "Memory Manager/Classes/Manager.h"

void run() {
    Manager manager(10*1024*1024); // MB 

    manager.ReceiveMessage("Create(4,int)"); // id 1
    manager.ReceiveMessage("Set(1,2)");


    manager.ReceiveMessage("Create(100,int)"); // id 2
    manager.ReceiveMessage("Set(2,27)");

    manager.ReceiveMessage("Create(4,float)"); // id 3
    manager.ReceiveMessage("Set(3,1.0)");

    manager.ReceiveMessage("DecreaseRefCount(2)");

    manager.ReceiveMessage("Create(2,char)"); // id 4
    manager.ReceiveMessage("Set(4,a)");

    manager.ReceiveMessage("Create(2,char)"); // id 5
    manager.ReceiveMessage("Set(5,z)");

}

int main(){
    run();
    return 0;
}