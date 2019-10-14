#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
int points;

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

void placeFood() {
    do {
        food.x = rand() % BUFFER_SIZE_X;
        food.y = rand() % BUFFER_SIZE_Y;
        if (buffer[food.x][food.y] == AIR) {
            buffer[food.x][food.y] = FOOD;
        }
    } while (buffer[food.x][food.y] != AIR && buffer[food.x][food.y] != FOOD);
}

int main(int argc, char const *argv[]) {
    // Seed the random generator
    srand(time(NULL));

    // Setup input
    char key = 0;
    setupEnterAvoidance();

    // Initialize game field
    clear(AIR);
    createGameField();
    player.x = BUFFER_SIZE_X / 2;
    player.y = BUFFER_SIZE_Y / 2;
    points = 0;
    placeFood();

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

        // Check new player position for food
        char replacefood = 0;
        if (buffer[player.x][player.y] == FOOD) {
            points++;
            replacefood = 1;
        }

        // Replace new position with player
        buffer[player.x][player.y] = PLAYER;

        // If food has been eaten, place new food
        if (replacefood) {
            placeFood();
        }

        // Print output
        printBuffer();
        printf("\nPoints: %d\n", points);
    }

    printf("\n");
    return 0;
}
