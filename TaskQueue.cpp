#include "TaskQueue.h"
#include <iostream>
using namespace std;

TaskQueue::TaskQueue() {
    // The queue starts empty using a sentinel (header) node
    header.next = nullptr;
    front = &header;
    back = &header;
}

TaskQueue::~TaskQueue() {
    Task temp;

    // Remove all remaining nodes from the queue
    while (dequeue(temp)) {
    }
}

void TaskQueue::enqueue(const Task& task) {
    // Create a new node to store the task
    Node* ptr = new Node;

    ptr->info = task;
    ptr->next = nullptr;

    // Add the new node to the end of the queue
    back->next = ptr;
    back = ptr;
}

bool TaskQueue::dequeue(Task& task) {
    // Return false if the queue is empty
    if (isEmpty()) {
        return false;
    }

    // Remove the node immediately after the sentinel node
    Node* ptr = front->next;

    // Store the removed task in the reference parameter
    task = ptr->info;
    front->next = ptr->next;

    // If the removed node was the last node,
    // update back to point to the sentinel node
    if (back == ptr) {
        back = front;
    }

    delete ptr;
    return true;
}

bool TaskQueue::removeById(int id) {
    // Return false if the queue is empty
    if (isEmpty()) {
        return false;
    }

    Node* current = front;

    // Search for the node containing the specified task ID
    while (current->next != nullptr) {
        if (current->next->info.getId() == id) {

            Node* temp = current->next;
            current->next = temp->next;

            // If the removed node was the last node,
            // update the back pointer
            if (back == temp) {
                back = current;
            }

            delete temp;
            return true;
        }

        current = current->next;
    }

    // Task ID was not found
    return false;
}

void TaskQueue::showQueue() const {
    // Display a message if the queue is empty
    if (isEmpty()) {
        cout << "No pending tasks in the queue." << endl;
        return;
    }

    Node* current = front->next;
    int count = 1;

    // Traverse the queue and display each pending task
    while (current != nullptr) {
        cout << "Pending Task #" << count << endl;
        current->info.display();
        cout << "--------------------------" << endl;

        current = current->next;
        count++;
    }
}

bool TaskQueue::isEmpty() const {
    // The queue is empty when both front and back
    // point to the sentinel node
    return front == back;
}