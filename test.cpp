#include <iostream>
#include "Memory Manager/Classes/Manager.h"

void run() {
    Manager manager(10*1024*1024); // MB 

    manager.ReceiveMessage("Create(2,int)");
    manager.ReceiveMessage("Create(2,int)");
    manager.ReceiveMessage("Set(2,1)");
    manager.ReceiveMessage("IncreaseRefCount(1)");
    manager.ReceiveMessage("DecreaseRefCount(1)");
    manager.ReceiveMessage("Create(10,double)");
    manager.ReceiveMessage("Create(10,char)");

}

int main(){
    run();
    return 0;
}