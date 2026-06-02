#ifndef DEPENDENCYGRAPH_H
#define DEPENDENCYGRAPH_H

#include "TaskList.h"
#include <string>

using namespace std;

// Graph class used to manage task dependencies
class DependencyGraph {
private:

    // Edge node represents a dependency connection
    struct EdgeNode {
        int dependentId;
        EdgeNode* next;

        EdgeNode(int id) {
            dependentId = id;
            next = nullptr;
        }
    };

    // Vertex node represents a task in the graph
    struct VertexNode {
        int taskId;
        EdgeNode* edges;
        VertexNode* next;

        VertexNode(int id) {
            taskId = id;
            edges = nullptr;
            next = nullptr;
        }
    };

    // Visit node is used during graph traversal
    struct VisitNode {
        int taskId;
        VisitNode* next;

        VisitNode(int id) {
            taskId = id;
            next = nullptr;
        }
    };

    // First vertex in the graph
    VertexNode* head;

    // Helper functions for graph management
    VertexNode* findVertex(int taskId) const;
    void addVertex(int taskId);

    // Helper functions for cycle detection
    bool hasPath(int startId, int targetId) const;
    bool hasPathHelper(int currentId, int targetId, VisitNode*& visited) const;
    bool wasVisited(int taskId, VisitNode* visited) const;
    void addVisited(int taskId, VisitNode*& visited) const;
    void clearVisited(VisitNode*& visited) const;

public:
    DependencyGraph();
    ~DependencyGraph();

    // Adds a dependency between two tasks
    bool addDependency(int prerequisiteId, int dependentId, TaskList& taskList);

    // Displays all dependencies
    void showDependencies() const;

    // Checks if adding a dependency would create a cycle
    bool createsCycle(int prerequisiteId, int dependentId) const;

    // Checks if a task can be completed
    bool canCompleteTask(int taskId, TaskList& taskList) const;

    // Saves all registered dependencies to a text file
    bool saveDependenciesToFile(const string& filename) const;

    // Loads dependencies from a text file
    bool loadDependenciesFromFile(const string& filename, TaskList& taskList);
};

#endif