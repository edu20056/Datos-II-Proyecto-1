#include <iostream>
#include "LinkedList.h"

#include "MPointers.h"

void test1() {

    try {
        // Initialize the MPointer system for each type
        MPointer<int>::Init("127.0.0.1", 5005);
        MPointer<float>::Init("127.0.0.1", 5005);
        MPointer<double>::Init("127.0.0.1", 5005);
        MPointer<char>::Init("127.0.0.1", 5005);
        MPointer<bool>::Init("127.0.0.1", 5005);
        
        // Instantiating and saving values in memory blocks

        // Integer type example
        MPointer<int> ptr_int = MPointer<int>::New();
        *ptr_int = 5;
        std::cout << "ID PTR_INT = " << &ptr_int << "\n";

        MPointer<int> ptr_int3 = MPointer<int>::New();
        *ptr_int3 = 3;

        // Copy assignment for integer type
        MPointer<int> ptr_int2;
        ptr_int2 = ptr_int;
        std::cout << "ID PTR_INT2 = " << &ptr_int2 << "\n";
        std::cout << "VALUE PTR_INT2 = " << *ptr_int2 << "\n";

        // Float type example
        MPointer<float> ptr_float = MPointer<float>::New();
        *ptr_float = 3.14f;
        std::cout << "ID PTR_FLOAT = " << &ptr_float << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void test2() {

    MPointer<int>::Init("127.0.0.1", 5005);

    // Create a linked list
    LinkedList<int> list;

    // Add elements
    list.insertEnd(10);
    list.insertEnd(20);
    list.insertFront(5);
    list.insertEnd(30);
    
    // Display the list
    list.display();
    
    // Search for values
    std::cout << "Searching for 20: " << (list.search(20) ? "Found" : "Not found") << std::endl;
    std::cout << "Searching for 25: " << (list.search(25) ? "Found" : "Not found") << std::endl;
    
    // Delete a node
    list.deleteNode(20);
    
    // Display the list after deletion
    std::cout << "After deleting 20:" << std::endl;
    list.display();
    
    // Get the size
    std::cout << "List size: " << list.size() << std::endl;
    
    // Access by position
    try {
        std::cout << "Element at position 1: " << list.get(1) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}

int main(){

    test2();
    
    return 0;
}