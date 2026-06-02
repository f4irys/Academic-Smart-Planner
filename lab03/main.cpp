#include <iostream>
#include <string>
#include "TaskList.h"
#include "TaskQueue.h"
#include "ActionStack.h"
#include "SearchIndex.h"
#include "DependencyGraph.h"

using namespace std;

void printLine() {
    cout << "------------------------------" << endl;
}

int readInt(string message) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (!cin.fail()) {
            cin.ignore(1000, '\n');
            return value;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number." << endl;
    }
}

string readNonEmptyLine(string message) {
    string value;

    do {
        cout << message;
        getline(cin, value);

        if (value.empty()) {
            cout << "This field cannot be empty." << endl;
        }

    } while (value.empty());

    return value;
}

int readPriority() {
    int priority;

    do {
        priority = readInt("Enter priority (1 = High, 2 = Medium, 3 = Low): ");

        if (priority < 1 || priority > 3) {
            cout << "Invalid priority. Please enter 1, 2, or 3." << endl;
        }

    } while (priority < 1 || priority > 3);

    return priority;
}

void showMenu() {
    cout << "\n==============================" << endl;
    cout << " SMART ACADEMIC TASK PLANNER" << endl;
    cout << "==============================" << endl;
    cout << "1. Create Task" << endl;
    cout << "2. Show All Tasks" << endl;
    cout << "3. Search Task by ID" << endl;
    cout << "4. Delete Task by ID" << endl;
    cout << "5. Show Pending Task Queue" << endl;
    cout << "6. Process Next Pending Task" << endl;
    cout << "7. Show Action History" << endl;
    cout << "8. Register Dependency" << endl;
    cout << "9. Show Dependencies" << endl;
    cout << "10. Check If Task Can Be Completed" << endl;
    cout << "11. Save Tasks to File" << endl;
    cout << "12. Load Tasks from File" << endl;
    cout << "13. Mark Task as Completed" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";
}

void createTask(TaskList& list, TaskQueue& taskQueue, ActionStack& history, SearchIndex& index) {
    int id;
    int priority;
    string title;
    string description;
    string course;
    string dueDate;

    cout << "\n--- CREATE TASK ---" << endl;
    printLine();

    id = readInt("Enter task ID: ");

    if (list.idExists(id)) {
        cout << "That ID already exists." << endl;
        return;
    }

    title = readNonEmptyLine("Enter title: ");
    description = readNonEmptyLine("Enter description: ");
    course = readNonEmptyLine("Enter course: ");
    priority = readPriority();
    dueDate = readNonEmptyLine("Enter due date (YYYY-MM-DD): ");

    Task newTask(id, title, description, course, priority, dueDate);

    if (list.addTask(newTask)) {
        Task* taskPtr = list.searchTaskById(id);

        taskQueue.enqueue(newTask);
        index.insert(id, taskPtr);
        history.push("Created task with ID " + to_string(id));

        cout << "Task created successfully." << endl;
        cout << "Task added to pending task queue." << endl;
        cout << "Task added to search index." << endl;
    } else {
        cout << "Could not create task." << endl;
    }
}

void searchTask(SearchIndex& index, ActionStack& history) {
    int id;

    cout << "\n--- SEARCH TASK BY ID ---" << endl;
    printLine();

    id = readInt("Enter task ID: ");

    Task* found = index.search(id);

    if (found != nullptr) {
        cout << "Task found using search index:" << endl;
        found->display();
        history.push("Searched task with ID " + to_string(id));
    } else {
        cout << "Task not found." << endl;
        history.push("Failed search for task with ID " + to_string(id));
    }
}

void deleteTask(TaskList& list, TaskQueue& taskQueue, ActionStack& history, SearchIndex& index) {
    int id;

    cout << "\n--- DELETE TASK BY ID ---" << endl;
    printLine();

    id = readInt("Enter task ID: ");

    if (list.deleteTaskById(id)) {
        taskQueue.removeById(id);
        index.remove(id);
        history.push("Deleted task with ID " + to_string(id));

        cout << "Task deleted successfully." << endl;
        cout << "Task removed from pending queue and search index." << endl;
    } else {
        cout << "Task not found." << endl;
    }
}

void processNextPendingTask(TaskQueue& taskQueue, ActionStack& history) {
    Task task;

    cout << "\n--- PROCESS NEXT PENDING TASK ---" << endl;
    printLine();

    if (taskQueue.dequeue(task)) {
        cout << "The following task was processed:" << endl;
        task.display();

        history.push("Processed pending task with ID " + to_string(task.getId()));
    } else {
        cout << "There are no pending tasks to process." << endl;
    }
}

void registerDependency(DependencyGraph& graph, TaskList& list, ActionStack& history) {
    int prerequisiteId;
    int dependentId;

    cout << "\n--- REGISTER DEPENDENCY ---" << endl;
    printLine();

    prerequisiteId = readInt("Enter prerequisite task ID: ");
    dependentId = readInt("Enter dependent task ID: ");

    if (graph.addDependency(prerequisiteId, dependentId, list)) {
        history.push("Registered dependency: task " + to_string(dependentId) +
                     " depends on task " + to_string(prerequisiteId));
    }
}

void checkTaskCompletion(DependencyGraph& graph, TaskList& list, ActionStack& history) {
    int id;

    cout << "\n--- CHECK IF TASK CAN BE COMPLETED ---" << endl;
    printLine();

    id = readInt("Enter task ID: ");

    if (graph.canCompleteTask(id, list)) {
        history.push("Checked task " + to_string(id) + ": can be completed");
    } else {
        history.push("Checked task " + to_string(id) + ": cannot be completed");
    }
}

void markTaskAsCompleted(TaskList& list, ActionStack& history) {

    int id;

    cout << "\n--- MARK TASK AS COMPLETED ---" << endl;
    printLine();

    id = readInt("Enter task ID: ");

    Task* task = list.searchTaskById(id);

    if (task == nullptr) {

        cout << "Task not found." << endl;
        return;
    }

    task->setStatus("Completed");

    cout << "Task marked as completed successfully." << endl;

    history.push("Marked task " + to_string(id) + " as completed");
}

void saveTasks(TaskList& list, ActionStack& history) {
    cout << "\n--- SAVE TASKS TO FILE ---" << endl;
    printLine();

    if (list.saveTasksToFile("tasks.txt")) {
        cout << "Tasks saved successfully in tasks.txt." << endl;
        history.push("Saved tasks to file");
    } else {
        cout << "Tasks could not be saved." << endl;
    }
}

void saveAllData(TaskList& list, ActionStack& history, DependencyGraph& graph) {
    cout << "\n--- SAVE DATA TO FILES ---" << endl;

    bool tasksSaved = list.saveTasksToFile("tasks.txt"); //save tasks to file
    bool historySaved = history.saveHistoryToFile("history.txt"); //save history to file
    bool dependenciesSaved = graph.saveDependenciesToFile("dependencies.txt"); //save dependencies to file

    if (tasksSaved) {
        cout << "Tasks saved successfully in tasks.txt." << endl;
    } else {
        cout << "Tasks could not be saved." << endl;
    }

    if (historySaved) {
        cout << "History saved successfully in history.txt." << endl;
    } else {
        cout << "History could not be saved." << endl;
    }

    if (dependenciesSaved) {
        cout << "Dependencies saved successfully in dependencies.txt." << endl;
    } else {
        cout << "Dependencies could not be saved." << endl;
    }

    if (tasksSaved && historySaved && dependenciesSaved) {
        cout << "All data was saved successfully." << endl;
        history.push("Saved all data to files");
    } else {
        cout << "Some data could not be saved." << endl;
    }
}

void loadAllData(TaskList& list, TaskQueue& taskQueue, SearchIndex& index, ActionStack& history, DependencyGraph& graph) {

    cout << "\n--- LOAD DATA FROM FILES ---" << endl;
    printLine();

    bool tasksLoaded = list.loadTasksFromFile("tasks.txt", taskQueue, index);

    if (tasksLoaded) {
        cout << "Tasks loaded successfully from tasks.txt." << endl;
    } else {
        cout << "Tasks could not be loaded." << endl;
    }

    bool dependenciesLoaded = graph.loadDependenciesFromFile("dependencies.txt", list);

    if (dependenciesLoaded) {
        cout << "Dependencies loaded successfully from dependencies.txt." << endl;
    } else {
        cout << "Dependencies could not be loaded." << endl;
    }

    if (tasksLoaded && dependenciesLoaded) {
        history.push("Loaded all data from files");
    }
}

int main() {
    TaskList list;
    TaskQueue taskQueue;
    ActionStack history;
    SearchIndex index;
    DependencyGraph graph;

    int option;

    do {
        showMenu();
        option = readInt("");

        switch (option) {
            case 1:
                createTask(list, taskQueue, history, index);
                break;

            case 2:
                cout << "\n--- ALL TASKS ---" << endl;
                printLine();
                list.showAllTasks();
                break;

            case 3:
                searchTask(index, history);
                break;

            case 4:
                deleteTask(list, taskQueue, history, index);
                break;

            case 5:
                cout << "\n--- PENDING TASK QUEUE ---" << endl;
                printLine();
                taskQueue.showQueue();
                break;

            case 6:
                processNextPendingTask(taskQueue, history);
                break;

            case 7:
                cout << "\n--- ACTION HISTORY ---" << endl;
                printLine();
                history.showHistory();
                break;

            case 8:
                registerDependency(graph, list, history);
                break;

            case 9:
                cout << "\n--- TASK DEPENDENCIES ---" << endl;
                printLine();
                graph.showDependencies();
                break;

            case 10:
                checkTaskCompletion(graph, list, history);
                break;

            case 11:
                saveAllData(list, history, graph);
                break;

            case 12:
                 loadAllData(list, taskQueue, index, history, graph);
                 break;
            
            case 13:
                markTaskAsCompleted(list, history);
                break;

            case 0:
                cout << "Program ended." << endl;
                break;

            default:
                cout << "Invalid option. Please choose a valid menu option." << endl;
        }

    } while (option != 0);

    return 0;
}