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
        ptr_int = 5;
        std::cout << "ID PTR_INT = " << &ptr_int << "\n";

        // Copy assignment for integer type
        MPointer<int> ptr_int2 = MPointer<int>::New();
        ptr_int2 = ptr_int;
        std::cout << "ID PTR_INT2 = " << &ptr_int2 << "\n";

        // Float type example
        MPointer<float> ptr_float = MPointer<float>::New();
        ptr_float = 3.14f;
        std::cout << "ID PTR_FLOAT = " << &ptr_float << "\n";

        // Double type example
        MPointer<double> ptr_double = MPointer<double>::New();
        ptr_double = 2.71;
        std::cout << "ID PTR_DOUBLE = " << &ptr_double << "\n";

        // Char type example
        MPointer<char> ptr_char = MPointer<char>::New();
        ptr_char = 'A';
        std::cout << "ID PTR_CHAR = " << &ptr_char << "\n";

        // Bool type example
        MPointer<bool> ptr_bool = MPointer<bool>::New();
        ptr_bool = true;
        std::cout << "ID PTR_BOOL = " << &ptr_bool << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}