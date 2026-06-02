#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include "Task.h"

// Queue class used to manage pending tasks
class TaskQueue {
private:

    // Node structure for the linked queue
    struct Node {
        Task info;      // Stores the task
        Node* next;     // Points to the next node in the queue
    };

    // Pointers to the front and back of the queue
    // A header node is used as a sentinel node
    Node* front;
    Node* back;
    Node header;

public:

    // Constructor
    // Initializes an empty queue
    TaskQueue();

    // Destructor
    // Frees all dynamically allocated nodes
    ~TaskQueue();

    // Adds a task to the end of the queue
    void enqueue(const Task& task);

    // Removes the task at the front of the queue
    // Returns true if successful, false if the queue is empty
    bool dequeue(Task& task);

    // Removes a specific task from the queue using its ID
    // Returns true if the task was found and removed
    bool removeById(int id);

    // Displays all pending tasks in the queue
    void showQueue() const;

    // Checks whether the queue is empty
    bool isEmpty() const;
};

#endif