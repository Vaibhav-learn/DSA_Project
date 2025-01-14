#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 200

// Define the structure for a node in the linked list
typedef struct Node {
    char music[MAX_LENGTH];
    struct Node *next;
} Node;

// Function to create a new node
Node *createNode(const char *music) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->music, music);
    newNode->next = NULL;
    return newNode;
}

// Function to add a new music to the end of the playlist
void addMusic(Node **head, const char *music) {
    Node *newNode = createNode(music);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to move up the list according to popularity or user's liking
void moveUp(Node **head, const char *music) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("Playlist is too short to move up.\n");
        return;
    }
    Node *prev = NULL;
    Node *current = *head;
    while (current != NULL && strcmp(current->music, music) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Music not found in the playlist.\n");
        return;
    }
    if (prev == NULL) {
        printf("Music is already at the top of the playlist.\n");
        return;
    }
    prev->next = current->next;
    current->next = *head;
    *head = current;
}

// Function to display the whole playlist
void displayPlaylist(Node *head) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    printf("Your Playlist:\n");
    while (head != NULL) {
        printf("%s\n", head->music);
        head = head->next;
    }
}

int main() {
    Node *playlist = NULL;
    int choice;
    char input[MAX_LENGTH];

    printf("Welcome to the Music Playlist Manager!\n");

    do {
        printf("\nMenu:\n");
        printf("1. Add Music\n");
        printf("2. Display Playlist\n");
        printf("3. Move Up in Playlist\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        fgets(input, sizeof(input), stdin);
        if (isdigit(input[0])) {
            choice = atoi(input);
            switch (choice) {
                case 1:
                    printf("Enter the name of the music: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = '\0'; // Remove newline character
                    addMusic(&playlist, input);
                    break;
                case 2:
                    displayPlaylist(playlist);
                    break;
                case 3:
                    printf("Enter the name of the music you want to move up: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = '\0'; 
                    moveUp(&playlist, input);
                    break;
                case 4:
                    printf("Exiting... Thank you!\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            printf("Invalid input. Please enter a valid choice.\n");
        }
    } while (choice != 4);

    return 0;
}