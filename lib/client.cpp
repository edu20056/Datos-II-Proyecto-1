#include <iostream>
#include "MPointers.h"

int main(){

    try {

        // MPtrs Initializers for each type
        MPointer<int>::Init("127.0.0.1", 5005);
        MPointer<float>::Init("127.0.0.1", 5005);
        MPointer<double>::Init("127.0.0.1", 5005);
        MPointer<char>::Init("127.0.0.1", 5005);
        MPointer<bool>::Init("127.0.0.1", 5005);
        
        // Instantiating && Saving of values in Memory Blocks
        MPointer<int> ptr_int = MPointer<int>::New();
        ptr_int = 5;

        MPointer<int> ptr_int2 = MPointer<int>::New();
        ptr_int2 = ptr_int;

        std::cout << "ID PTR_INT = " << &ptr_int;
        std::cout << "ID PTR_INT2 = " << &ptr_int2;

        MPointer<float> ptr_float = MPointer<float>::New();
        ptr_float = 3.14f;

        MPointer<double> ptr_double = MPointer<double>::New();
        ptr_double = 2.71;

        MPointer<char> ptr_char = MPointer<char>::New();
        ptr_char = 'A';

        MPointer<bool> ptr_bool = MPointer<bool>::New();
        ptr_bool = true;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}