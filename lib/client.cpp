#include <iostream>
#include "LinkedList.h"

#include "MPointers.h"

void BasicTest_int() {
    
    try {
        std::cout << "\n=== Test: Integer (int) ===\n";
        
        // Create a new MPointer for int and initialize it with a value
        MPointer<int> num = MPointer<int>::New();
        *num = 42;

        // Display the value of *num and its memory address
        std::cout << "\nInitial Value: *num = " << *num 
                  << " | Memory Address: &num = " << &num << '\n';
        
        // Modify the value and display again
        *num = *num + 10;
        std::cout << "Modified Value: *num = " << *num 
                  << " | Memory Address: &num = " << &num << '\n';
        
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
    }
}

void Test_MultipleTypes() {

    try {
        // Create instances of each pointer type
        MPointer<int> integer = MPointer<int>::New();
        MPointer<float> floatingPoint = MPointer<float>::New();
        MPointer<double> doublePrecision = MPointer<double>::New();
        MPointer<char> character = MPointer<char>::New();
        MPointer<bool> boolean = MPointer<bool>::New();
        
        // Assign values to each pointer
        *integer = 42;
        *floatingPoint = 3.1416f;
        *doublePrecision = 2.718281828459045;
        *character = 'X';
        *boolean = true;
        
        // Display values and their memory addresses
        std::cout << "\n=== Assigned Values and Memory Addresses ===\n";
        
        std::cout << "Integer: " << *integer 
                  << " | Memory Address: " << &integer << std::endl;
        std::cout << "Floating Point: " << *floatingPoint 
                  << " | Memory Address: " << &floatingPoint << std::endl;
        std::cout << "Double Precision: " << *doublePrecision 
                  << " | Memory Address: " << &doublePrecision << std::endl;
        std::cout << "Character: " << *character 
                  << " | Memory Address: " << &character << std::endl;
        std::cout << "Boolean: " << (*boolean ? "true" : "false") 
                  << " | Memory Address: " << &boolean << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
    }
}

void AsignationTest() {

    try {
        std::cout << "\n=== Example of Assignment Between MPointers ===\n";
        
        // Create two MPointers and assign initial values
        MPointer<int> a = MPointer<int>::New();
        *a = 100;
        
        MPointer<int> b = MPointer<int>::New();
        *b = 200;
        
        // Display the initial values of a and b
        std::cout << "Initial Values: a = " << *a << ", b = " << *b << '\n';
        
        // Assign MPointer b to MPointer a
        a = b;
        std::cout << "\nAfter Assignment (a = b):\n";
        std::cout << "Value of a: " << *a << ", Value of b: " << *b << '\n';
        
        // Modify one pointer, which will affect the other (same reference)
        *a = 300;
        std::cout << "\nAfter Modifying *a = 300:\n";
        std::cout << "Value of a: " << *a << ", Value of b: " << *b << '\n';
        
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
    }
}

void ErrorTest() {

    try {
        std::cout << "\n=== Error Handling Example ===\n";
        
        // Try to use an uninitialized MPointer
        try {
            MPointer<float> temp = MPointer<float>::New();
            *temp = 3.14f;  // Attempting to dereference an uninitialized pointer
        } catch (const std::exception& e) {
            std::cout << "Expected Error (uninitialized): " << e.what() << std::endl;
        }
        
        // Initialize MPointer system
        MPointer<float>::Init("127.0.0.1", 5005);
        
        // Create a valid MPointer and assign a value
        MPointer<float> validPointer = MPointer<float>::New();
        *validPointer = 2.718f;
        
        // Try to use a null MPointer
        MPointer<float> nullPointer;
        try {
            *nullPointer = 1.414f;  // Attempt to dereference a null pointer
        } catch (const std::exception& e) {
            std::cout << "Expected Error (null MPointer): " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "\nUnexpected Error: " << e.what() << std::endl;
    }
}

int main(){

    try {

        // Initialize the MPointer system for each type
        MPointer<int>::Init("127.0.0.1", 5005);
        MPointer<float>::Init("127.0.0.1", 5005);
        MPointer<double>::Init("127.0.0.1", 5005);
        MPointer<char>::Init("127.0.0.1", 5005);
        MPointer<bool>::Init("127.0.0.1", 5005);
        
        // TESTS...

        //BasicTest_int();
        //Test_MultipleTypes();
        AsignationTest();
        //ErrorTest(); // Comment the <float> Init


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}