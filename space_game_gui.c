
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h> // For usleep
#include <time.h>
#include <ctype.h>


#define MAPHEIGHT 24
#define MAPWIDTH 24

char T[MAPWIDTH][MAPHEIGHT];

void generateMap() {

    int playerPosY = 4;
    int playerPosX = 4;

    T[MAPHEIGHT][MAPWIDTH];

    for (int i = 0; i < MAPHEIGHT; i++) {
        for (int j = 0; j < MAPWIDTH; j++) {
            T[i][j] = '#';
        }
    }
}

void singularHashtagDraw(int playerPosX, int playerPosY) {
    T[playerPosY][playerPosX] = '#';
}


void reDrawMap(int playerPosX, int playerPosY, int state) {

    switch (state) { 
        case 1:
            T[playerPosY][playerPosX] = '*';

        
            for (int i = 0; i < MAPHEIGHT; i++) {
                for (int j = 0; j < MAPWIDTH; j++) {
                    printf("%c " ,T[i][j]);
                }   
                printf("\n");
            }
        break;

        case 2:
            // Draw shop.
            

        break;
    }
}

int getSizeX() {
    return MAPWIDTH;
}

int getSizeY() {
    return MAPHEIGHT;
}

