#ifndef TODO_H
#define TODO_H

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
#define MAX_LENGTH 256

typedef struct {
    char description[MAX_LENGTH];
    char tag[MAX_LENGTH];
    char deadline[MAX_LENGTH];
    int priority;
    int done; // 0=pending, 1=done, 2=missed
} Task;

typedef struct {
    char name[MAX_LENGTH];
    Task* tasks;
    int count;
    int capacity;
} TaskList;

void addList(const char* listName);
int selectList();
void addTask(int listIndex);
void viewTasks(int listIndex);
void viewLists();
void markDone(int listIndex, int taskIndex);
void deleteTask(int listIndex, int taskIndex);
void searchTask(int listIndex);
void sortTasks(int listIndex);
void cleanup();

#endif
