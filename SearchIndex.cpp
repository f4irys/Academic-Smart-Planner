#include "SearchIndex.h"

// Constructor
// Initializes all hash table positions to nullptr
SearchIndex::SearchIndex() {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

// Destructor
// Frees all dynamically allocated nodes in the hash table
SearchIndex::~SearchIndex() {
    for (int i = 0; i < SIZE; i++) {
        Node* current = table[i];

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

// Hash function
// Generates an index based on the task ID
int SearchIndex::hashFunction(int id) const {
    return id % SIZE;
}

// Insert function
// Adds a task pointer into the hash table
void SearchIndex::insert(int id, Task* taskPtr) {
    int index = hashFunction(id);

    Node* newNode = new Node(id, taskPtr);

    // Insert at the beginning of the linked list
    newNode->next = table[index];
    table[index] = newNode;
}

// Search function
// Searches for a task by ID in the hash table
Task* SearchIndex::search(int id) const {
    int index = hashFunction(id);

    Node* current = table[index];

    while (current != nullptr) {

        // Check if the ID matches
        if (current->id == id) {
            return current->taskPtr;
        }

        current = current->next;
    }

    // Task was not found
    return nullptr;
}

// Remove function
// Removes a task from the hash table using its ID
bool SearchIndex::remove(int id) {
    int index = hashFunction(id);

    Node* current = table[index];
    Node* previous = nullptr;

    while (current != nullptr) {

        // Check if the ID matches
        if (current->id == id) {

            // Remove first node in the list
            if (previous == nullptr) {
                table[index] = current->next;
            }

            // Remove middle or last node
            else {
                previous->next = current->next;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    // Task was not found
    return false;
}