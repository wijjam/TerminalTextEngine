#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h> // For usleep
#include <time.h>
#include <ctype.h>

static struct termios original_termios;

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