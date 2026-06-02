#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

using namespace std;

// Class that represents a single academic task
class Task {
private:
    int id;                 // Unique task identifier
    string title;           // Task title
    string description;     // Task description
    string course;          // Associated course
    int priority;           // Task priority (1 = High, 2 = Medium, 3 = Low)
    string dueDate;         // Due date
    string status;          // Task status (Pending or Completed)

public:
    // Default constructor
    Task();

    // Constructor with parameters
    Task(int id,
         string title,
         string description,
         string course,
         int priority,
         string dueDate,
         string status = "Pending");

    // Getter methods
    int getId() const;
    string getTitle() const;
    string getDescription() const;
    string getCourse() const;
    int getPriority() const;
    string getDueDate() const;
    string getStatus() const;

    // Updates the task status
    void setStatus(string status);

    // Converts priority number into text
    string priorityToString() const;

    // Displays task information
    void display() const;
};

#endif