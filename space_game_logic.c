#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h> // For usleep
#include <time.h>
#include <ctype.h>
#include "space_game_gui.h"
#include "linked_list.h"


static struct termios original_termios;
Node* EnemyList;


void enableRawMode() {
    tcgetattr(STDIN_FILENO, &original_termios); // Save original settings
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // Disable echo, canonical mode, signal chars
    raw.c_cc[VMIN] = 0;                     // Read returns immediately if no char
    raw.c_cc[VTIME] = 0;                    // Non-blocking read (0 timeout)
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Apply new settings
}

// Restores the terminal to its original settings
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

int generateRandomX() {
    return rand() % getSizeX();
}

int generateRandomY() {
    return rand() % getSizeY();
}

void initEnemy() {
    EnemyList = createEmpty();
}


void spawnEnemy() {

    int randX = generateRandomX();
    int randY = generateRandomY();

    enemy newEnemy;
    newEnemy.posX = randX;
    newEnemy.posY = randY;
    newEnemy.health = 10;
    addAtEnd(&EnemyList, newEnemy);

    drawEnemy(newEnemy);
}


void moveEnemy(int playerPosY, int playerPosX) {

    Node* EnemyListTemp = EnemyList;
    while (EnemyListTemp != NULL) {
        singularHashtagDraw(EnemyListTemp->data.posY ,EnemyListTemp->data.posX);

        if (EnemyListTemp->data.posY < playerPosY) {
            EnemyListTemp->data.posY = EnemyListTemp->data.posY + 1;
        } else if (EnemyListTemp->data.posY == playerPosY) {
            // Do nothing
        } else if (EnemyListTemp->data.posY > playerPosY) {
            EnemyListTemp->data.posY = EnemyListTemp->data.posY - 1;
        }

        drawEnemy(EnemyListTemp->data);
        EnemyListTemp = EnemyListTemp->next;
    }


}



