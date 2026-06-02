#ifndef SEARCHINDEX_H
#define SEARCHINDEX_H

#include "Task.h"

// Hash table class used for efficient task searching by ID
class SearchIndex {

private:

    // Size of the hash table
    static const int SIZE = 101;

    // Node structure for separate chaining
    struct Node {
        int id;
        Task* taskPtr;
        Node* next;

        // Node constructor
        Node(int id, Task* taskPtr) {
            this->id = id;
            this->taskPtr = taskPtr;
            next = nullptr;
        }
    };

    // Array of linked list pointers
    Node* table[SIZE];

    // Hash function to calculate the table index
    int hashFunction(int id) const;

public:

    // Constructor
    SearchIndex();

    // Destructor
    ~SearchIndex();

    // Inserts a task into the hash table
    void insert(int id, Task* taskPtr);

    // Searches for a task by ID
    Task* search(int id) const;

    // Removes a task from the hash table
    bool remove(int id);
};

#endif