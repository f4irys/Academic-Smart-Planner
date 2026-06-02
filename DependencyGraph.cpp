#include "DependencyGraph.h"
#include <iostream>
#include <fstream>

using namespace std;

DependencyGraph::DependencyGraph() {
    head = nullptr;
}

DependencyGraph::~DependencyGraph() {
    VertexNode* currentVertex = head;

    while (currentVertex != nullptr) {
        EdgeNode* currentEdge = currentVertex->edges;

        while (currentEdge != nullptr) {
            EdgeNode* tempEdge = currentEdge;
            currentEdge = currentEdge->next;
            delete tempEdge;
        }

        VertexNode* tempVertex = currentVertex;
        currentVertex = currentVertex->next;
        delete tempVertex;
    }
}

// Finds a vertex by task ID
DependencyGraph::VertexNode* DependencyGraph::findVertex(int taskId) const {
    VertexNode* current = head;

    while (current != nullptr) {
        if (current->taskId == taskId) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

// Adds a new vertex if it does not already exist
void DependencyGraph::addVertex(int taskId) {
    if (findVertex(taskId) != nullptr) {
        return;
    }

    VertexNode* newVertex = new VertexNode(taskId);
    newVertex->next = head;
    head = newVertex;
}

// Registers a dependency between two tasks
bool DependencyGraph::addDependency(int prerequisiteId, int dependentId, TaskList& taskList) {
    if (prerequisiteId == dependentId) {
        cout << "A task cannot depend on itself." << endl;
        return false;
    }

    if (taskList.searchTaskById(prerequisiteId) == nullptr) {
        cout << "Prerequisite task does not exist." << endl;
        return false;
    }

    if (taskList.searchTaskById(dependentId) == nullptr) {
        cout << "Dependent task does not exist." << endl;
        return false;
    }

    addVertex(prerequisiteId);
    addVertex(dependentId);

    VertexNode* prerequisiteVertex = findVertex(prerequisiteId);

    EdgeNode* current = prerequisiteVertex->edges;

    while (current != nullptr) {
        if (current->dependentId == dependentId) {
            cout << "This dependency already exists." << endl;
            return false;
        }

        current = current->next;
    }

     // Prevent dependencies that create cycles
    if (createsCycle(prerequisiteId, dependentId)) {
        cout << "This dependency cannot be added because it creates a cycle." << endl;
        return false;
    }

    EdgeNode* newEdge = new EdgeNode(dependentId);
    newEdge->next = prerequisiteVertex->edges;
    prerequisiteVertex->edges = newEdge;

    cout << "Dependency registered successfully." << endl;
    cout << "Task " << dependentId << " depends on task " << prerequisiteId << "." << endl;

    return true;
}
// Displays all registered dependencies
void DependencyGraph::showDependencies() const {
    if (head == nullptr) {
        cout << "No dependencies registered." << endl;
        return;
    }

    VertexNode* currentVertex = head;

    while (currentVertex != nullptr) {
        cout << "Task " << currentVertex->taskId << " must be completed before: ";

        if (currentVertex->edges == nullptr) {
            cout << "No dependent tasks";
        } else {
            EdgeNode* currentEdge = currentVertex->edges;

            while (currentEdge != nullptr) {
                cout << currentEdge->dependentId;

                if (currentEdge->next != nullptr) {
                    cout << ", ";
                }

                currentEdge = currentEdge->next;
            }
        }

        cout << endl;
        currentVertex = currentVertex->next;
    }
}

// Checks whether a task ID has already been visited
bool DependencyGraph::wasVisited(int taskId, VisitNode* visited) const {
    VisitNode* current = visited;

    while (current != nullptr) {
        if (current->taskId == taskId) {
            return true;
        }

        current = current->next;
    }

    return false;
}

// Adds a task ID to the visited list
void DependencyGraph::addVisited(int taskId, VisitNode*& visited) const {
    VisitNode* newNode = new VisitNode(taskId);
    newNode->next = visited;
    visited = newNode;
}

// Clears the visited list to prevent memory leaks
void DependencyGraph::clearVisited(VisitNode*& visited) const {
    while (visited != nullptr) {
        VisitNode* temp = visited;
        visited = visited->next;
        delete temp;
    }
}

// Checks if a path exists between two vertices
bool DependencyGraph::hasPath(int startId, int targetId) const {
    VisitNode* visited = nullptr;

    bool result = hasPathHelper(startId, targetId, visited);

    clearVisited(visited);

    return result;
}

// Recursive graph traversal function
bool DependencyGraph::hasPathHelper(int currentId, int targetId, VisitNode*& visited) const {
    if (currentId == targetId) {
        return true;
    }

    if (wasVisited(currentId, visited)) {
        return false;
    }

    addVisited(currentId, visited);

    VertexNode* currentVertex = findVertex(currentId);

    if (currentVertex == nullptr) {
        return false;
    }

    EdgeNode* currentEdge = currentVertex->edges;

    while (currentEdge != nullptr) {
        if (hasPathHelper(currentEdge->dependentId, targetId, visited)) {
            return true;
        }

        currentEdge = currentEdge->next;
    }

    return false;
}

// Checks if adding a dependency would create a cycle
bool DependencyGraph::createsCycle(int prerequisiteId, int dependentId) const {
    return hasPath(dependentId, prerequisiteId);
}

// Checks whether a task can be completed
bool DependencyGraph::canCompleteTask(int taskId, TaskList& taskList) const {
    Task* task = taskList.searchTaskById(taskId);

    if (task == nullptr) {
        cout << "Task does not exist." << endl;
        return false;
    }

    VertexNode* currentVertex = head;

    while (currentVertex != nullptr) {
        EdgeNode* currentEdge = currentVertex->edges;

        while (currentEdge != nullptr) {
            if (currentEdge->dependentId == taskId) {
                Task* prerequisiteTask = taskList.searchTaskById(currentVertex->taskId);

                if (prerequisiteTask == nullptr) {
                    cout << "A prerequisite task no longer exists." << endl;
                    return false;
                }

                if (prerequisiteTask->getStatus() != "Completed") {
                    cout << "Task " << taskId << " cannot be completed yet." << endl;
                    cout << "Reason: it depends on task " << currentVertex->taskId;
                    cout << ", which is not completed." << endl;
                    return false;
                }
            }

            currentEdge = currentEdge->next;
        }

        currentVertex = currentVertex->next;
    }

    cout << "Task " << taskId << " can be completed." << endl;
    return true;
}

// Saves all dependencies to a text file
bool DependencyGraph::saveDependenciesToFile(const string& filename) const {
    ofstream file(filename);

   // check if the file was opened successfully
    if (!file) {
        cout << "Error: Could not open dependencies file for saving." << endl;
        return false;
    }

    VertexNode* currentVertex = head;

    while (currentVertex != nullptr) {
        EdgeNode* currentEdge = currentVertex->edges;

        while (currentEdge != nullptr) {
            file << currentVertex->taskId << "|"
                 << currentEdge->dependentId << endl;

            currentEdge = currentEdge->next;
        }

        currentVertex = currentVertex->next;
    }

    file.close();

    return true;

    }
    // Loads dependencies from a text file
    bool DependencyGraph::loadDependenciesFromFile(const string& filename, TaskList& taskList) {
    ifstream file(filename);

    if (!file) {
        cout << "Error: Could not open dependencies file for loading." << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    while (getline(file, line)) {
        int separatorPos = line.find('|');

        if (separatorPos == -1) {
            cout << "Warning: Invalid dependency line skipped." << endl;
            continue;
        }

        int prerequisiteId = stoi(line.substr(0, separatorPos));
        int dependentId = stoi(line.substr(separatorPos + 1));

        if (addDependency(prerequisiteId, dependentId, taskList)) {
            loadedCount++;
        }
    }

    file.close();

    cout << loadedCount << " dependencies loaded successfully from " << filename << "." << endl;

    return true;
}
    
