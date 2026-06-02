#include "ActionStack.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
// Initializes the stack as empty by setting top to nullptr
ActionStack::ActionStack() {
    top = nullptr;
}

// Destructor
// Frees all dynamically allocated nodes from the stack
ActionStack::~ActionStack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

// Push function
// Adds a new action to the top of the stack
void ActionStack::push(string action) {
    Node* newNode = new Node(action);

    // Link the new node to the current top
    newNode->next = top;

    // Update top to point to the new node
    top = newNode;
}

// Checks if the stack is empty
bool ActionStack::isEmpty() const {
    return top == nullptr;
}

// Displays the action history
// The most recent action appears first
void ActionStack::showHistory() const {

    // Check if the stack is empty
    if (isEmpty()) {
        cout << "No actions in history." << endl;
        return;
    }

    Node* current = top;
    int count = 1;

    // Traverse the stack and display each action
    while (current != nullptr) {
        cout << count << ". " << current->action << endl;

        current = current->next;
        count++;
    }
}

// Saves the action history to a file
bool ActionStack::saveHistoryToFile(const string& filename) const {
    ofstream file(filename);

    if (!file) {
        cout << "Error: Could not open history file for saving." << endl;
        return false;
    }

    Node* current = top;

    while (current != nullptr) {
        file << current->action << endl;
        current = current->next;
    }

    file.close();

    return true;
}