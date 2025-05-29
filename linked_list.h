#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h> // For bool type

// --- Data Structure for Enemy ---
// This typedef defines the 'enemy' structure.
typedef struct {
    int posY;
    int posX;
    int health;
} enemy;

// --- Node Structure for Linked List ---
// This typedef defines a single node in the linked list.
// Each node holds an 'enemy' and a pointer to the next node.
typedef struct Node {
    enemy data;
    struct Node *next;
} Node;

// --- Function Prototypes ---

Node* createEmpty();

/**
 * @brief Creates a new node with the given enemy data.
 * @param newEnemy The enemy data to be stored in the new node.
 * @return A pointer to the newly created node, or NULL if memory allocation fails.
 */
Node* createNode();


/**
 * @brief Adds a new node to the beginning of the linked list.
 * @param head A pointer to the head of the list (will be updated if new node becomes head).
 * @param newEnemy The enemy data to add.
 */
void addAtBeginning(Node **head, enemy newEnemy);

/**
 * @brief Adds a new node to the end of the linked list.
 * @param head A pointer to the head of the list.
 * @param newEnemy The enemy data to add.
 */
void addAtEnd(Node **head, enemy newEnemy);

/**
 * @brief Deletes the first occurrence of a node containing a specific enemy.
 * Matching is based on posX, posY, and health.
 * @param head A pointer to the head of the list (will be updated if head is deleted).
 * @param targetEnemy The enemy data to search for and delete.
 * @return true if the enemy was found and deleted, false otherwise.
 */
bool deleteNode(Node **head, enemy targetEnemy);

/**
 * @brief Searches for a node containing a specific enemy.
 * Matching is based on posX, posY, and health.
 * @param head The head of the list.
 * @param targetEnemy The enemy data to search for.
 * @return A pointer to the found node, or NULL if not found.
 */
Node* searchNode(Node *head, enemy targetEnemy);

/**
 * @brief Prints the data of all enemies in the linked list.
 * @param head The head of the list.
 */
void printList(Node *head);

/**
 * @brief Frees all memory allocated for the linked list.
 * @param head A pointer to the head of the list (will be set to NULL after freeing).
 */
void freeList(Node **head);

/**
 * @brief Gets the current size (number of nodes) of the linked list.
 * @param head The head of the list.
 * @return The number of nodes in the list.
 */
int getListSize(Node *head);

#endif // LINKED_LIST_H