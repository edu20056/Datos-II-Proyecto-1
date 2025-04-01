
// Code Adapted From [CodeSignal - Introduction to Linked Lists in C++]
// (https://codesignal.com/learn/courses/fundamental-data-structures-linked-lists-in-cpp/lessons/introduction-to-linked-lists-in-cpp)

class Node {
    public:
        int data;      // Node data
        Node* next;    // Pointer to next node
    
        Node(int data) : data(data), next(nullptr) {}  // Initialize node with data
    };

        
class LinkedList {
    private:
        Node* head;    // Pointer to first node

    public:
        LinkedList() : head(nullptr) {}  // Initialize empty list

        ~LinkedList() {
            Node* current = head;  // Start with the head node
    
            while (current != nullptr) {  // Iterate until the end of the list
                Node* nextNode = current->next;  // Store the next node
                delete current;  // Delete the current node
                current = nextNode;  // Move to the next node
            }
        }

        void append(int data) {
            Node* node = new Node(data);  // Create new node
            if (!head) {
                head = node;  // Set head if list is empty
            } else {
                Node* last = head;
                while (last->next) {
                    last = last->next;  // Traverse to end
                }
                last->next = node;  // Append new node
            }
        }

    void addFirst(int data) {
        Node* node = new Node(data); // Create new node

        if (head != nullptr) {
            node->next = head; // Link new node to the current head
        }

        head = node; // Update head to new node
    }

    void deleteNode(int data) {
        if (head == nullptr) return;  // Check if list is empty

        // Check if the head node is the one to be deleted

        if (head->data == data) {
            Node* temp = head;
            head = head->next;  // Move head to the next node
            delete temp;  // Free memory of the old head
            return;
        }

        Node* current = head;

        // Traverse the list to find the node to delete
        while (current->next != nullptr) {
            if (current->next->data == data) {
                Node* temp = current->next;
                current->next = current->next->next;  // Bypass the node to delete
                delete temp;  // Free memory of the bypassed node
                return;
            }

            current = current->next;  // Move to the next node
        }
    }
};