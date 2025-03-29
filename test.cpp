#include <iostream>
#include "Memory Manager/Classes/Manager.h"

void run() {
    Manager manager(10);

    manager.ReceiveMessage("Create(10,string)");
    manager.ReceiveMessage("Create(4,int)");
    manager.ReceiveMessage("Set(1,A)");
    manager.ReceiveMessage("IncreaseRefCount(1)");
    manager.ReceiveMessage("DecreaseRefCount(1)");

    
    //Another example
    //manager.ReceiveMessage("Create(4,int)");
    //manager.ReceiveMessage("Create(2,string)");
    //manager.ReceiveMessage("Set(2,A)");
    //manager.ReceiveMessage("IncreaseRefCount(1)");
    //manager.ReceiveMessage("DecreaseRefCount(1)");

}

int main(){
    run();
    return 0;
}