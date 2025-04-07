#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>

#include "MPointers.h"

// Code Adapted From [CodeSignal - Introduction to Linked Lists in C++]
// (https://codesignal.com/learn/courses/fundamental-data-structures-linked-lists-in-cpp/lessons/introduction-to-linked-lists-in-cpp)


template <typename T>
class LinkedList {
private:

    struct Node {
        MPointer<T> data;  // Data stored as MPointer
        int nextIndex;     // Index of the next node in vector
    };
    
    std::vector<Node> nodes;       // All stored nodes
    int headIndex;                 // Head's Index

public:

    LinkedList() : headIndex(-1) {}
    
    void insertFront(T value) {

        MPointer<T> newData = MPointer<T>::New();
        *newData = value;
        
        // Create new node
        Node newNode;
        newNode.data = newData;
        newNode.nextIndex = headIndex;
        
        // Add node to vector
        nodes.push_back(newNode);
        
        // Update head index to point to the new node
        headIndex = nodes.size() - 1;
    }
    
    void insertEnd(T value) {

        MPointer<T> newData = MPointer<T>::New();
        *newData = value;
        
        // Create new node
        Node newNode;
        newNode.data = newData;
        newNode.nextIndex = -1;
        
        if (headIndex == -1) {
            nodes.push_back(newNode);
            headIndex = 0;
            return;
        }
        
        int currentIndex = headIndex;
        while (nodes[currentIndex].nextIndex != -1) {
            currentIndex = nodes[currentIndex].nextIndex;
        }
        
        // Add node to vector
        nodes.push_back(newNode);
        
        // Update last node to point to new node
        nodes[currentIndex].nextIndex = nodes.size() - 1;
    }
    
    bool deleteNode(T value) {
        if (headIndex == -1) {
            return false; // List is empty
        }
        
        // Special case: head contains the value
        if (*nodes[headIndex].data == value) {
            int oldHead = headIndex;
            headIndex = nodes[headIndex].nextIndex;
           
            return true;
        }
        
        // Search for the value in the list
        int currentIndex = headIndex;
        while (nodes[currentIndex].nextIndex != -1) {
            int nextIndex = nodes[currentIndex].nextIndex;
            if (*nodes[nextIndex].data == value) {
                // Found the value, update pointer to skip this node
                nodes[currentIndex].nextIndex = nodes[nextIndex].nextIndex;
                
                // Actual Node remains in vector but is disconnected from the logical list
                return true;
            }
            currentIndex = nextIndex;
        }
        
        return false; // Value not found
    }
    
    void display() {
        std::cout << "List contents: ";
        
        if (headIndex == -1) {
            std::cout << "Empty list \n";
            return;
        }
        
        // Traverse the list
        int currentIndex = headIndex;
        while (currentIndex != -1) {
            std::cout << *nodes[currentIndex].data << " -> ";
            currentIndex = nodes[currentIndex].nextIndex;
        }
        
        std::cout << "NULL \n";
    }

    int size() {
        int count = 0;
        int currentIndex = headIndex;
        
        while (currentIndex != -1) {
            count++;
            currentIndex = nodes[currentIndex].nextIndex;
        }
        
        return count;
    }
    
    bool search(T value) {
        int currentIndex = headIndex;
        
        while (currentIndex != -1) {
            if (*nodes[currentIndex].data == value) {
                return true; // Value found
            }
            currentIndex = nodes[currentIndex].nextIndex;
        }
        
        return false; // Value not found
    }
    
    T get(int position) {
        if (headIndex == -1 || position < 0) {
            throw std::out_of_range("Invalid position or empty list");
        }
        
        int currentIndex = headIndex;
        int currentPos = 0;
        
        while (currentIndex != -1 && currentPos < position) {
            currentIndex = nodes[currentIndex].nextIndex;
            currentPos++;
        }
        
        if (currentIndex == -1) {
            throw std::out_of_range("Position exceeds list size");
        }
        
        return *nodes[currentIndex].data;
    }
};

#endif 