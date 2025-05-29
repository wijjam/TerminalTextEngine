#include "linked_list.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

// Helper function to check if two enemy structs are equal
static bool areEnemiesEqual(enemy e1, enemy e2) {
    return (e1.posX == e2.posX && e1.posY == e2.posY && e1.health == e2.health);
}

Node* createEmpty() {
    return NULL;
}

Node* createNode(enemy newEnemy) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        return NULL; // Memory allocation failed
    }
    newNode->data = newEnemy; // Assign the enemy data
    newNode->next = NULL;     // New node points to NULL initially
    return newNode;
}

void addAtBeginning(Node **head, enemy newEnemy) {
    Node *newNode = createNode(newEnemy);
    if (newNode == NULL) {
        return; // Failed to create node
    }
    newNode->next = *head; // New node points to the current head
    *head = newNode;       // New node becomes the new head
}

void addAtEnd(Node **head, enemy newEnemy) {
    Node *newNode = createNode(newEnemy);
    if (newNode == NULL) {
        return; // Failed to create node
    }

    if (*head == NULL) {
        *head = newNode; // If list is empty, new node is the head
        return;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next; // Traverse to the last node
    }
    current->next = newNode; // Last node points to the new node
}

bool deleteNode(Node **head, enemy targetEnemy) {
    if (*head == NULL) {
        return false; // List is empty
    }

    Node *current = *head;
    Node *prev = NULL;

    // If the head node contains the target enemy
    if (areEnemiesEqual(current->data, targetEnemy)) {
        *head = current->next; // Move head to the next node
        free(current);         // Free the old head node
        return true;
    }

    // Search for the target enemy in the rest of the list
    while (current != NULL && !areEnemiesEqual(current->data, targetEnemy)) {
        prev = current;
        current = current->next;
    }

    // If enemy was not found
    if (current == NULL) {
        return false;
    }

    // Enemy found, unlink the node and free it
    prev->next = current->next;
    free(current);
    return true;
}

Node* searchNode(Node *head, enemy targetEnemy) {
    Node *current = head;
    while (current != NULL) {
        if (areEnemiesEqual(current->data, targetEnemy)) {
            return current; // Found the node
        }
        current = current->next;
    }
    return NULL; // Node not found
}

void printList(Node *head) {
    Node *current = head;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Linked List (Enemy Data):\n");
    while (current != NULL) {
        printf("  Enemy: (posX: %d, posY: %d, health: %d)\n",
               current->data.posX, current->data.posY, current->data.health);
        current = current->next;
    }
}

void freeList(Node **head) {
    Node *current = *head;
    Node *next;
    while (current != NULL) {
        next = current->next; // Store the next node before freeing current
        free(current);        // Free the current node
        current = next;       // Move to the next node
    }
    *head = NULL; // Set head to NULL after freeing all nodes
    printf("List memory freed.\n");
}

int getListSize(Node *head) {
    int count = 0;
    Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}