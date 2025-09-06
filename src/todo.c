#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

static TaskList* lists = NULL;
static int listCount = 0;
static int listCapacity = 0;

void addList(const char* listName) {
    if (listCount == listCapacity) {
        int newCapacity = listCapacity == 0 ? 5 : listCapacity * 2;
        TaskList* temp = realloc(lists, sizeof(TaskList) * newCapacity);
        if (!temp) {
            fprintf(stderr, "Failed to allocate memory for lists.\n");
            return;
        }
        lists = temp;
        listCapacity = newCapacity;
    }
    strncpy(lists[listCount].name, listName, MAX_LENGTH-1);
    lists[listCount].name[MAX_LENGTH-1] = '\0';
    lists[listCount].tasks = NULL;
    lists[listCount].count = 0;
    lists[listCount].capacity = 0;
    listCount++;
}

int selectList() {
    if (listCount == 0) {
        printf("No lists available. Please add a list first.\n");
        return -1;
    }
    printf("\nAvailable Lists:\n");
    for (int i = 0; i < listCount; i++) {
        printf("%d. %s\n", i + 1, lists[i].name);
    }
    printf("Select list number: ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // Clear input buffer
        return -1;
    }
    getchar();
    if (choice < 1 || choice > listCount) return -1;
    return choice - 1;
}

void addTask(int listIndex) {
    if (listIndex < 0 || listIndex >= listCount) return;

    TaskList* list = &lists[listIndex];

    if (list->count == list->capacity) {
        int newCap = list->capacity == 0 ? 5 : list->capacity * 2;
        Task* temp = realloc(list->tasks, sizeof(Task) * newCap);
        if (!temp) {
            fprintf(stderr, "Failed to allocate memory for tasks.\n");
            return;
        }
        list->tasks = temp;
        list->capacity = newCap;
    }

    Task t;
    printf("Enter task description: ");
    if (!fgets(t.description, MAX_LENGTH, stdin)) return;
    t.description[strcspn(t.description, "\n")] = 0;

    printf("Enter priority (1=High, 2=Medium, 3=Low): ");
    if (scanf("%d", &t.priority) != 1 || t.priority < 1 || t.priority > 3) {
        printf("Invalid priority, setting to Low (3).\n");
        t.priority = 3;
    }
    getchar();

    printf("Enter tag (Work/Personal/etc): ");
    if (!fgets(t.tag, MAX_LENGTH, stdin)) return;
    t.tag[strcspn(t.tag, "\n")] = 0;

    printf("Enter deadline (YYYY-MM-DD): ");
    if (!fgets(t.deadline, MAX_LENGTH, stdin)) return;
    t.deadline[strcspn(t.deadline, "\n")] = 0;

    t.done = 0; // Pending
    list->tasks[list->count++] = t;

    printf("Task added successfully.\n");
}

void viewTasks(int listIndex) {
    if (listIndex < 0 || listIndex >= listCount) return;

    TaskList* list = &lists[listIndex];
    if (list->count == 0) {
        printf("No tasks in list '%s'.\n", list->name);
        return;
    }

    printf("\nTasks in list '%s':\n", list->name);
    for (int i = 0; i < list->count; i++) {
        Task* t = &list->tasks[i];
        char* symbol;
        char* color;

        if (t->done == 0) { symbol = "✖"; color = RED; }
        else if (t->done == 1) { symbol = "✔"; color = GREEN; }
        else { symbol = "⚠"; color = YELLOW; }

        printf("%d. %s[%s]%s %s (Priority: %d, Tag: %s, Deadline: %s)\n",
            i + 1, color, symbol, RESET, t->description, t->priority, t->tag, t->deadline);
    }
}

void viewLists() {
    if (listCount == 0) {
        printf("No lists available.\n");
        return;
    }
    printf("\nAvailable Lists:\n");
    for (int i = 0; i < listCount; i++) {
        printf("%d. %s\n", i + 1, lists[i].name);
    }
}

void markDone(int listIndex, int taskIndex) {
    if (listIndex < 0 || listIndex >= listCount) return;
    TaskList* list = &lists[listIndex];
    if (taskIndex < 0 || taskIndex >= list->count) {
        printf("Invalid task number!\n");
        return;
    }
    list->tasks[taskIndex].done = 1;
    printf("Task '%s' marked as done!\n", list->tasks[taskIndex].description);
}

void deleteTask(int listIndex, int taskIndex) {
    if (listIndex < 0 || listIndex >= listCount) return;
    TaskList* list = &lists[listIndex];
    if (taskIndex < 0 || taskIndex >= list->count) {
        printf("Invalid task number!\n");
        return;
    }
    for (int i = taskIndex; i < list->count - 1; i++) {
        list->tasks[i] = list->tasks[i + 1];
    }
    list->count--;
    printf("Task deleted successfully.\n");
}

void searchTask(int listIndex) {
    if (listIndex < 0 || listIndex >= listCount) return;
    TaskList* list = &lists[listIndex];
    if (list->count == 0) {
        printf("No tasks to search.\n");
        return;
    }

    char keyword[MAX_LENGTH];
    printf("Enter keyword to search: ");
    if (!fgets(keyword, MAX_LENGTH, stdin)) return;
    keyword[strcspn(keyword, "\n")] = 0;

    int found = 0;
    printf("Search results in list '%s':\n", list->name);
    for (int i = 0; i < list->count; i++) {
        if (strstr(list->tasks[i].description, keyword)) {
            printf("%d. %s\n", i + 1, list->tasks[i].description);
            found = 1;
        }
    }

    if (!found)
        printf("No tasks found matching '%s'.\n", keyword);
}

void sortTasks(int listIndex) {
    if (listIndex < 0 || listIndex >= listCount) return;
    TaskList* list = &lists[listIndex];
    if (list->count < 2) return;

    for (int i = 0; i < list->count - 1; i++) {
        for (int j = i + 1; j < list->count; j++) {
            if (list->tasks[i].priority > list->tasks[j].priority) {
                Task temp = list->tasks[i];
                list->tasks[i] = list->tasks[j];
                list->tasks[j] = temp;
            }
        }
    }
    printf("Tasks sorted by priority.\n");
}

void cleanup() {
    for (int i = 0; i < listCount; i++) {
        free(lists[i].tasks);
    }
    free(lists);
}
