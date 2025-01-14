#include <stdio.h> // For input and output functions
#include <stdlib.h> // For dynamic memory allocation
#include <stdbool.h> // For boolean data type
#include <string.h> // For string handling functions

// Structure representing a single task node in the to-do list
typedef struct TaskNode {
    char task[100]; // Task description
    bool completed; // Status of the task (completed or not)
    struct TaskNode* next; // Pointer to the next task node
} TaskNode;

// Structure representing the to-do list
typedef struct {
    TaskNode* head; // Pointer to the first task in the list
    TaskNode* tail; // Pointer to the last task in the list
} ToDoList;

// Initialize the to-do list
void initializeList(ToDoList* list) {
    list->head = NULL; // Set head to NULL, indicating an empty list
    list->tail = NULL; // Set tail to NULL, indicating an empty list
}

// Add a new task to the to-do list
void addTask(ToDoList* list, char task[]) {
    TaskNode* newTask = (TaskNode*)malloc(sizeof(TaskNode)); // Allocate memory for a new task node
    if (newTask == NULL) { // Check if memory allocation failed
        printf("Memory allocation failed.\n");
        exit(1); // Exit the program if allocation fails
    }
    strcpy(newTask->task, task); // Copy the task description into the new node
    newTask->completed = false; // Set the task status to incomplete
    newTask->next = NULL; // Initialize the next pointer to NULL

    if (list->head == NULL) { // If the list is empty
        list->head = newTask; // Set the new task as the head
        list->tail = newTask; // Set the new task as the tail
    } else { // If the list is not empty
        list->tail->next = newTask; // Append the new task at the end
        list->tail = newTask; // Update the tail pointer
    }
}

// Mark a task as completed
void completeTask(ToDoList* list, char task[]) {
    TaskNode* current = list->head; // Start at the head of the list
    while (current != NULL) { // Traverse the list
        if (strcmp(current->task, task) == 0) { // If the task matches
            current->completed = true; // Mark the task as completed
            return; // Exit the function
        }
        current = current->next; // Move to the next node
    }
    printf("Task \"%s\" not found.\n", task); // Print an error if the task is not found
}

// Print the to-do list
void printList(ToDoList* list) {
    printf("To-Do List:\n"); // Print header
    TaskNode* current = list->head; // Start at the head of the list
    while (current != NULL) { // Traverse the list
        printf("%s - %s\n", current->completed ? "[X]" : "[ ]", current->task); // Print task with status
        current = current->next; // Move to the next node
    }
}

// Remove all completed tasks from the to-do list
void removeCompletedTasks(ToDoList* list) {
    TaskNode* current = list->head; // Start at the head of the list
    TaskNode* prev = NULL; // Previous node pointer, initially NULL
    while (current != NULL) { // Traverse the list
        if (current->completed) { // If the task is completed
            if (current == list->head) { // If it's the first node
                list->head = current->next; // Update the head pointer
            } else { // If it's not the first node
                prev->next = current->next; // Remove the current node from the list
            }
            TaskNode* temp = current; // Temporary pointer for the node to be freed
            current = current->next; // Move to the next node
            free(temp); // Free the memory of the removed node
        } else { // If the task is not completed
            prev = current; // Update the previous pointer
            current = current->next; // Move to the next node
        }
    }
}

// Main function
int main() {
    ToDoList list;
    initializeList(&list); // Initialize the to-do list
    int choice;
    char task[100];

    do {
        // Display menu options
        printf("\nMenu:\n");
        printf("1. Add Task\n");
        printf("2. Mark Task as Completed\n");
        printf("3. Remove Completed Tasks\n");
        printf("4. View To-Do List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Take user input for menu choice

        switch (choice) {
            case 1:
                printf("Enter task: ");
                scanf(" %[^\n]", task); // Read task description
                addTask(&list, task); // Add the task to the list
                printf("Task added successfully!\n");
                break;
            case 2:
                printf("Enter task to mark as completed: ");
                scanf(" %[^\n]", task); // Read task description
                completeTask(&list, task); // Mark the task as completed
                printf("Task marked as completed!\n");
                break;
            case 3:
                removeCompletedTasks(&list); // Remove all completed tasks
                printf("Completed tasks removed!\n");
                break;
            case 4:
                printList(&list); // Print the entire to-do list
                break;
            case 5:
                printf("Exiting...\n"); // Exit message
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n"); // Invalid input message
        }
    } while (choice != 5); // Continue until the user chooses to exit

    return 0;
}

