#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a call
struct call {
    char callerName[50];    // Stores the caller's name
    int phoneNumber[15];    // Stores the caller's phone number
    struct call *next;      // Pointer to the next call in the list
};

// Function to create a new call node
struct call *createCallNode(char callerName[], int phoneNumber[]) {
    struct call *newCall = (struct call *)malloc(sizeof(struct call)); // Allocate memory for the new call
    if (newCall == NULL) { // Check for memory allocation failure
        printf("Memory allocation failed.\n");
        exit(1);
    }
    
    // Initialize the new call node
    strcpy(newCall->callerName, callerName); // Copy caller name
    memcpy(newCall->phoneNumber, phoneNumber, sizeof(newCall->phoneNumber)); // Copy phone number
    newCall->next = NULL; // Set the next pointer to NULL
    return newCall;  
}

// Function to push a call onto the stack
void push(struct call *top, char callerName[], int phoneNumber[]) {
    struct call *newCall = createCallNode(callerName, phoneNumber); // Create a new call node
    newCall->next = top; // Point the new call's next to the current top
    top = newCall; // Update the stack's top
    printf("Call from %s added to the stack.\n", callerName);
}

// Function to pop a call from the stack
void pop(struct call *top) {
    if (top == NULL) { // Check if the stack is empty
        printf("The call stack is empty.\n");
        return;
    }
    struct call *temp = top; // Save the current top for deletion
    top = top->next; // Move the top to the next call
    printf("Call from %s removed from the stack.\n", temp->callerName);
    free(temp); // Free the memory of the removed call
}

// Function to enqueue a call to the queue
void enqueue(struct call *rear, char callerName[], int phoneNumber[]) {
    struct call *newCall = createCallNode(callerName, phoneNumber); // Create a new call node
    if (rear == NULL) { // If the queue is empty
        rear = newCall; // Set the new call as the rear
    } else {
        rear->next = newCall; // Add the new call at the end of the queue
        rear = newCall; // Update the rear pointer
    }
    printf("Call from %s added to the queue.\n", callerName);
}

// Function to dequeue a call from the queue
void dequeue(struct call *front) {
    if (front == NULL) { // Check if the queue is empty
        printf("The call queue is empty.\n");
        return;
    }
    struct call *temp = front; // Save the current front for deletion
    front = front->next; // Move the front to the next call
    printf("Call from %s removed from the queue.\n", temp->callerName);
    free(temp); // Free the memory of the removed call
}

// Function to display all calls in the stack
void displayStack(struct call *top) {
    if (top == NULL) { // Check if the stack is empty
        printf("The call stack is empty.\n");
        return;
    }
    printf("Call Stack:\n");
    while (top != NULL) { // Traverse the stack
        printf("Caller: %s, Phone Number: %s\n", top->callerName, top->phoneNumber);
        top = top->next; // Move to the next call
    }
}

// Function to display all calls in the queue
void displayQueue(struct call *front) {
    if (front == NULL) { // Check if the queue is empty
        printf("The call queue is empty.\n");
        return;
    }
    printf("Call Queue:\n");
    while (front != NULL) { // Traverse the queue
        printf("Caller: %s, Phone Number: %s\n", front->callerName, front->phoneNumber);
        front = front->next; // Move to the next call
    }
}

int main() {
    struct call *stackTop = NULL; // Pointer to the top of the stack
    struct call *queueFront = NULL; // Pointer to the front of the queue
    struct call *queueRear = NULL; // Pointer to the rear of the queue
    int choice, phoneNumber[15];
    char callerName[50];

    // Menu-driven program for call management
    while (1) {
        printf("\nCall Management System Menu:\n");
        printf("1. Add a Call to Stack\n");
        printf("2. Remove Last Call from Stack\n");
        printf("3. Display All Calls in Stack\n");
        printf("4. Add a Call to Queue\n");
        printf("5. Remove First Call from Queue\n");
        printf("6. Display All Calls in Queue\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter caller name: ");
                scanf("%s", callerName);
                printf("Enter phone number: ");
                scanf("%s", phoneNumber); // Taking phone number input as a string
                push(stackTop, callerName, phoneNumber); // Add the call to the stack
                break;
            case 2:
                pop(stackTop); // Remove the top call from the stack
                break;
            case 3:
                displayStack(stackTop); // Display all calls in the stack
                break;
            case 4:
                printf("Enter caller name: ");
                scanf("%s", callerName);
                printf("Enter phone number: ");
                scanf("%s", phoneNumber); // Taking phone number input as a string
                enqueue(queueRear, callerName, phoneNumber); // Add the call to the queue
                if (queueFront == NULL) { // If the queue was empty, update the front pointer
                    queueFront = queueRear;
                }
                break;
            case 5:
                dequeue(queueFront); // Remove the front call from the queue
                break;
            case 6:
                displayQueue(queueFront); // Display all calls in the queue
                break;
            case 7:
                printf("Exiting...\n"); // Exit the program
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
