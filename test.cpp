#include <iostream>
#include "Memory Manager/Classes/Manager.h"
#include "MPointers/Classes/client.h"

void run() {
    Client cliente ("127.0.0.1", 5005);
    cliente.createConnection();

    string stringMessage = cliente.sendAndReceive("Create(10,int)");
    cout <<  stringMessage << endl;

    string stringMessage1 = cliente.sendAndReceive("Set(1,17)");
    cout <<  stringMessage1 << endl;


    string stringMessage2 = cliente.sendAndReceive("Get(1)");
    cout <<  stringMessage2 << endl;


    //Manager test

    /*    
    Manager manager(10*1024*1024); // MB 

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
    
    */

    manager.ReceiveMessage("Create(4,int)"); 
    manager.ReceiveMessage("Set(1,2)");
}

void newRun() {
    MPointer<int>::Init(50000);
        
    MPointer<int> ptr1;
    ptr1.New();
    ptr1 *= 42; 
    
    MPointer<int> ptr2 = ptr1;
    std::cout << "Value: " << *ptr2 << std::endl;
}

int main(){
    newRun();
    return 0;
}


/* PENDIENTES....

1 > Arreglar MPointers/Client
2 > Arreglar operador *__=__ && Static New
3 > Garbage Collect
4 > Linked Lists + Examples
5 > Docs

*/