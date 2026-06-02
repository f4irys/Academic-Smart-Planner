#ifndef ACTIONSTACK_H
#define ACTIONSTACK_H

#include <string>

using namespace std;

// Stack class used to store action history
class ActionStack {

private:

    // Node structure for the linked stack
    struct Node {
        string action;
        Node* next;

        // Node constructor
        Node(string a) {
            action = a;
            next = nullptr;
        }
    };

    // Pointer to the top of the stack
    Node* top;

public:

    // Constructor
    ActionStack();

    // Destructor
    ~ActionStack();

    // Adds a new action to the stack
    void push(string action);

    // Displays all actions in the stack
    void showHistory() const;

    // Checks if the stack is empty
    bool isEmpty() const;

    // Saves the action history to a file
    bool saveHistoryToFile(const string& filename) const;
};

#endif