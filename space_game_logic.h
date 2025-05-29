#ifndef GAME_LOGIC
#define GAME_LOGIC

extern struct termios original_termios;


extern struct enemy* enemies;

void enableRawMode();
void disableRawMode();

int generateRandomX();
int generateRandomY();

void initEnemy();

void spawnEnemy();

void moveEnemy(int playerPosX, int playerPosY);


#endif