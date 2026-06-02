#include "TaskList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Constructor: initializes an empty task list
TaskList::TaskList() {
    head = nullptr;
}

// Destructor: frees all dynamically allocated nodes
TaskList::~TaskList() {
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// Adds a new task to the linked list
bool TaskList::addTask(const Task& task) {
    if (idExists(task.getId())) {
        return false;
    }

    Node* newNode = new Node(task);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    return true;
}

// Displays all tasks stored in the list
void TaskList::showAllTasks() const {
    if (head == nullptr) {
        cout << "No tasks available." << endl;
        return;
    }

    Node* current = head;

    while (current != nullptr) {
        current->data.display();
        cout << "--------------------------" << endl;
        current = current->next;
    }
}

// Searches for a task using its ID
Task* TaskList::searchTaskById(int id) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.getId() == id) {
            return &(current->data);
        }
        current = current->next;
    }

    return nullptr;
}

// Deletes a task from the list using its ID
bool TaskList::deleteTaskById(int id) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.getId() == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;

    while (current->next != nullptr) {
        if (current->next->data.getId() == id) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return true;
        }
        current = current->next;
    }

    return false;
}

// Checks whether a task ID already exists
bool TaskList::idExists(int id) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.getId() == id) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Saves all tasks to a text file
bool TaskList::saveTasksToFile(const string& filename) const {
    ofstream file(filename);

    if (!file) {
        cout << "Error: Could not open file for saving." << endl;
        return false;
    }

    Node* current = head;

    while (current != nullptr) {
        file << current->data.getId() << "|"
             << current->data.getTitle() << "|"
             << current->data.getDescription() << "|"
             << current->data.getCourse() << "|"
             << current->data.getPriority() << "|"
             << current->data.getDueDate() << "|"
             << current->data.getStatus() << endl;

        current = current->next;
    }

    file.close();

    return true;
}

// Loads tasks from a file and rebuilds the system structures
bool TaskList::loadTasksFromFile(const string& filename, TaskQueue& taskQueue, SearchIndex& index) {
    ifstream file(filename);

    if (!file) {
        cout << "Error: Could not open file for loading." << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    while (getline(file, line)) {
        string idText, title, description, course, priorityText, dueDate, status;

        stringstream ss(line);

        getline(ss, idText, '|');
        getline(ss, title, '|');
        getline(ss, description, '|');
        getline(ss, course, '|');
        getline(ss, priorityText, '|');
        getline(ss, dueDate, '|');
        getline(ss, status, '|');

        if (idText.empty() || title.empty() || priorityText.empty()) {
            cout << "Warning: Invalid task line skipped." << endl;
            continue;
        }

        int id;
        int priority;

        try {
            id = stoi(idText);
            priority = stoi(priorityText);
        } catch (...) {
            cout << "Warning: Invalid number format skipped." << endl;
            continue;
        }

        if (idExists(id)) {
            cout << "Warning: Task ID " << id << " already exists. Skipped." << endl;
            continue;
        }

        Task task(id, title, description, course, priority, dueDate, status);

        if (addTask(task)) {
            Task* taskPtr = searchTaskById(id);

            taskQueue.enqueue(task);
            index.insert(id, taskPtr);

            loadedCount++;
        }
    }

    file.close();

    cout << loadedCount << " tasks loaded successfully from " << filename << "." << endl;

    return true;
}