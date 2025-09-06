#include <stdio.h>
#include "todo.h"

int main() {
    int choice;
    int lastListIndex = -1;

    do {
        printf("\n--- TO-DO LIST ---\n");
        printf("1. Add List\n2. Add Task\n3. View Tasks\n4. Mark Done\n5. Delete Task\n6. Search Task\n7. Sort Tasks\n0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Clear invalid input
            printf("Invalid input, try again.\n");
            continue;
        }
        getchar();

        int listIndex, taskNumber;
        switch (choice) {
            case 1: {
                char name[MAX_LENGTH];
                printf("Enter list name: ");
                if (!fgets(name, MAX_LENGTH, stdin)) break;
                name[strcspn(name, "\n")] = 0;
                addList(name);
                break;
            }
            case 2:
                if (lastListIndex == -1) {
                    listIndex = selectList();
                    lastListIndex = listIndex;
                } else {
                    listIndex = lastListIndex;
                }
                if (listIndex != -1) addTask(listIndex);
                break;
            case 3:
                if (lastListIndex == -1) {
                    listIndex = selectList();
                    lastListIndex = listIndex;
                } else {
                    listIndex = lastListIndex;
                }
                if (listIndex != -1) viewTasks(listIndex);
                break;
            case 4:
                if (lastListIndex == -1) {
                    listIndex = selectList();
                    lastListIndex = listIndex;
                } else {
                    listIndex = lastListIndex;
                }
                if (listIndex != -1) {
                    viewTasks(listIndex);
                    printf("Enter task number to mark done: ");
                    if (scanf("%d", &taskNumber) == 1) {
                        getchar();
                        markDone(listIndex, taskNumber - 1);
                    } else {
                        while (getchar() != '\n');
                        printf("Invalid task number.\n");
                    }
                }
                break;
            case 5:
                if (lastListIndex == -1) {
                    listIndex = selectList();
                    lastListIndex = listIndex;
                } else {
                    listIndex = lastListIndex;
                }
                if (listIndex != -1) {
                    viewTasks(listIndex);
                    printf("Enter task number to delete: ");
                    if (scanf("%d", &taskNumber) == 1) {
                        getchar();
                        deleteTask(listIndex, taskNumber - 1);
                    } else {
                        while (getchar() != '\n');
                        printf("Invalid task number.\n");
                    }
                }
                break;
            case 6:
                if (lastListIndex == -1) {
                    listIndex = selectList();
                    lastListIndex = listIndex;
                } else {
                    listIndex = lastListIndex;
                }
                if (listIndex != -1) searchTask(listIndex);
                break;
            case 7:
                if (lastListIndex == -1) {
                    listIndex = selectList();
                    lastListIndex = listIndex;
                } else {
                    listIndex = lastListIndex;
                }
                if (listIndex != -1) {
                    sortTasks(listIndex);
                    viewTasks(listIndex);
                }
                break;
            case 0:
                printf("Exiting program. Cleaning up...\n");
                cleanup();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
