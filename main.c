#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h> // For usleep
#include <time.h>
#include <ctype.h>
#include "space_game_logic.h"
#include "space_game_gui.h"


#define TARGET_FPS 60
#define TARGET_FRAME_TIME_NS (1000000000LL / TARGET_FPS)


int main() {

    char user_input;

    enableRawMode(); // Put terminal into raw input mode
    atexit(disableRawMode); // Ensure terminal is restored on exit

    int isInGame = 1;

    int playerPosX = 4;
    int playerPosY = 4;
    long long target_enemy_nanoseconds = 0;
    long long elapsed_nanoseconds = 1;
    struct timespec start, current, start_enemy, current_enemy_time;
    int64_t elaps;

    srand(time(NULL));

    generateMap();
    clock_gettime(CLOCK_MONOTONIC, &start);
    

    while (1) { // Infinite loop
        clock_gettime(CLOCK_MONOTONIC, &current);
       

        elaps = (current.tv_sec - start.tv_sec) * 1000000000LL + (current.tv_nsec - start.tv_nsec);

        if (elaps < TARGET_FRAME_TIME_NS) {
            int64_t time_to_sleep = TARGET_FRAME_TIME_NS - elaps;

            usleep(time_to_sleep / 1000);
        }

        if (elapsed_nanoseconds > target_enemy_nanoseconds) {
            clock_gettime(CLOCK_MONOTONIC, &start_enemy);
            target_enemy_nanoseconds = (long long)start_enemy.tv_sec * 1000000000LL + start_enemy.tv_nsec + (10 * 1000000000LL);
        }
        clock_gettime(CLOCK_MONOTONIC, &current_enemy_time);
        elapsed_nanoseconds = (long long)current_enemy_time.tv_sec * 1000000000LL + current_enemy_time.tv_nsec;

        singularHashtagDraw(playerPosX, playerPosY);
        if (read(STDIN_FILENO, &user_input, 1) == 1) {
            char lower_char = (char)tolower((unsigned char)user_input); // Convert to lowercase
            
            switch(lower_char) {
             case 'q': printf("\nQuitting...\n"); return; // Exit the loop

             case 'w': if (playerPosY > 0 && isInGame == 1) {playerPosY = playerPosY - 1;} break;
             case 'a': if (playerPosX > 0 && isInGame == 1) {playerPosX = playerPosX - 1; } break;
             case 's': if (playerPosY < getSizeY()-1 && isInGame == 1) {playerPosY = playerPosY + 1; } break;
             case 'd': if (playerPosX < getSizeX()-1 && isInGame == 1) {playerPosX = playerPosX + 1;} break;
             case 'e': disableRawMode(); isInGame = 0; break;
            }
        }
        
        reDrawMap(playerPosX, playerPosY, 1);
        fflush(stdout); // Make sure output appears immediately
        printf("\033c");
        clock_gettime(CLOCK_MONOTONIC, &start);
    }

    return 0;
}