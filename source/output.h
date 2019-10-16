#ifndef output_h
#define output_h

#include <stdio.h>

#define BUFFER_SIZE_X 64
#define BUFFER_SIZE_Y 16

// Screen buffer
char buffer[BUFFER_SIZE_X][BUFFER_SIZE_Y] = {};

// Replace the entire buffer with a given char
void clear(char c) {
    for (int y = 0; y < BUFFER_SIZE_Y; y++) {
        for (int x = 0; x < BUFFER_SIZE_X; x++) {
            buffer[x][y] = c;
        }
    }
}

// Method to output the buffer to terminal by printing it
void printBuffer() {
    for (int y = 0; y < BUFFER_SIZE_Y; y++) {
        printf("\n");
        for (int x = 0; x < BUFFER_SIZE_X; x++) {
            printf("%c", buffer[x][y]);
        }
    }
}
#endif