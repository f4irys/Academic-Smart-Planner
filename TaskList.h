#ifndef TASKLIST_H
#define TASKLIST_H

#include "Task.h"
#include "TaskQueue.h"
#include "SearchIndex.h"
#include <string>

using namespace std;

// Linked list class used to store and manage tasks
class TaskList {
private:

    // Node structure for the linked list
    struct Node {
        Task data;      // Stores task information
        Node* next;     // Points to the next node

        Node(const Task& t) {
            data = t;
            next = nullptr;
        }
    };

    // Pointer to the first node in the list
    Node* head;

public:

    // Constructor
    TaskList();

    // Destructor
    ~TaskList();

    // Adds a new task to the list
    bool addTask(const Task& task);

    // Displays all tasks
    void showAllTasks() const;

    // Searches for a task by ID
    Task* searchTaskById(int id);

    // Deletes a task by ID
    bool deleteTaskById(int id);

    // Checks if an ID already exists
    bool idExists(int id) const;

    // Saves all tasks to a file
    bool saveTasksToFile(const string& filename) const;

    // Loads tasks from a file
    bool loadTasksFromFile(const string& filename,
                           TaskQueue& taskQueue,
                           SearchIndex& index);
};

#endif