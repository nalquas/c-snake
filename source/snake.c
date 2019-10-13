#include <stdio.h>
#include "input.h"
#include "output.h"

#define WALL '#'
#define PLAYER 'S'
#define FOOD 'F'
#define AIR ' '

struct block {
    int x;
    int y;
} player, food;

void createGameField() {
    // Walls
    for (int x = 0; x < BUFFER_SIZE_X; x++) {
        buffer[x][0] = WALL;
        buffer[x][BUFFER_SIZE_Y - 1] = WALL;
    }
    for (int y = 0; y < BUFFER_SIZE_Y; y++) {
        buffer[0][y] = WALL;
        buffer[BUFFER_SIZE_X - 1][y] = WALL;
    }
}

int main(int argc, char const *argv[]) {
    char key = 0;
    setupEnterAvoidance();

    clear(AIR);
    createGameField();
    player.x = BUFFER_SIZE_X / 2;
    player.y = BUFFER_SIZE_Y / 2;

    // Game loop
    while (key != 'q') {
        // Get Input
        key = readInput();

        // Replace old position with wall
        buffer[player.x][player.y] = WALL;

        // Update player position
        switch (key) {
            case 'w':
                player.y--;
                break;
            case 's':
                player.y++;
                break;
            case 'a':
                player.x--;
                break;
            case 'd':
                player.x++;
                break;
            default:
                break;
        }

        // Replace new position with player
        buffer[player.x][player.y] = PLAYER;

        // Print output
        printBuffer();
    }

    printf("\n");
    return 0;
}
