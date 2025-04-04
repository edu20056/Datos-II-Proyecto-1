#include <iostream>
#include "LinkedList.h"

#include "MPointers.h"

int main(){

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
        return 1;
    }
    
    return 0;
}