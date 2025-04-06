#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "MPointers.h"

// Code Adapted From [CodeSignal - Introduction to Linked Lists in C++]
// (https://codesignal.com/learn/courses/fundamental-data-structures-linked-lists-in-cpp/lessons/introduction-to-linked-lists-in-cpp)


template<typename T>
class Node {
    
    public:
        MPointer<T> data;      // Node data
        MPointer<Node<T>> next;    // Pointer to next node
    
        Node() = default;

        Node(T value) {   // Initialize node with data
            data = MPointer<T>::New();
            *data = value;
            next = nullptr;
        }  
    };

template<typename T>    
class LinkedList {
    
    private:

        MPointer<Node<T>> head;    // Pointer to first node

    public:

        LinkedList() : head(nullptr) {}  // Initialize empty list

        void append(T value) {

            // Create and initialize a new node
            MPointer<Node<T>> newNode = MPointer<Node<T>>::New();
            *newNode = Node<T>(value);
    
            // If list is empty, make new node the head
            if (head == nullptr) {
                head = newNode;
            } else {
                // Otherwise, traverse to the end and append the node
                MPointer<Node<T>> current = head;
                while ((*current).next != nullptr) {
                    current = (*current).next;
                }
                (*current).next = newNode;
            }
        }

        void addFirst(T value) {

            // Create and initialize a new node
            MPointer<Node<T>> newNode = MPointer<Node<T>>::New();
            *newNode = Node<T>(value);

            // Point the new node's next to current head
            (*newNode).next = head;

            // Update head to point to the new node
            head = newNode;
        }

        void deleteNode(T value) {
            // If the list is empty, there's nothing to delete
            if (head == nullptr) return;

            // If the head node holds the value, remove it
            if (*((*head).data) == value) {
                head = (*head).next;
                return;
            }

            // Traverse the list to find the node before the one to delete
            MPointer<Node<T>> current = head;
            while ((*current).next != nullptr) {
                if (*((*(*current).next).data) == value) {
                    // Skip over the node to delete
                    (*current).next = (*(*current).next).next;
                    return;
                }
                current = (*current).next;
            }
        }

        void printList() {
            MPointer<Node<T>> current = head;
            while (current != nullptr) {
                std::cout << *((*current).data) << " -> ";
                current = (*current).next;
            }
            std::cout << "null" << std::endl;
        }
};

#endif 