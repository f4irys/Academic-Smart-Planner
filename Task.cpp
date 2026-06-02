#include "Task.h"

using namespace std;

// Default constructor
// Initializes a task with default values
Task::Task() {
    id = 0;
    title = "";
    description = "";
    course = "";
    priority = 3;
    dueDate = "";
    status = "Pending";
}

// Constructor with parameters
// Initializes a task with user-provided values
Task::Task(int id, string title, string description, string course, int priority, string dueDate, string status) {
    this->id = id;
    this->title = title;
    this->description = description;
    this->course = course;
    this->priority = priority;
    this->dueDate = dueDate;
    this->status = status;
}

// Returns the task ID
int Task::getId() const {
    return id;
}

// Returns the task title
string Task::getTitle() const {
    return title;
}

// Returns the task description
string Task::getDescription() const {
    return description;
}

// Returns the associated course
string Task::getCourse() const {
    return course;
}

// Returns the task priority
int Task::getPriority() const {
    return priority;
}

// Returns the due date
string Task::getDueDate() const {
    return dueDate;
}

// Returns the task status
string Task::getStatus() const {
    return status;
}

// Updates the task status
void Task::setStatus(string status) {
    this->status = status;
}

// Converts the numeric priority into text
string Task::priorityToString() const {
    if (priority == 1) {
        return "High";
    } else if (priority == 2) {
        return "Medium";
    } else {
        return "Low";
    }
}

// Displays all task information
void Task::display() const {
    cout << "[" << id << "] " << title << endl;
    cout << "Description: " << description << endl;
    cout << "Course: " << course << endl;
    cout << "Priority: " << priorityToString() << endl;
    cout << "Due Date: " << dueDate << endl;
    cout << "Status: " << status << endl;
}