#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 5
#define MAX_MOVES 100

typedef struct {
    int monkeyX, monkeyY;    // Monkey position
    int boxX, boxY;          // Box position
    bool onBox;              // Is monkey on box?
    bool hasBanana;          // Has monkey got banana?
    char move[50];           // Description of move
} State;

// Check if move is valid within room bounds
bool isValidMove(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// Try to solve the puzzle using a simple state-space search
void solvePuzzle(int bananaX, int bananaY) {
    State moves[MAX_MOVES];
    int moveCount = 0;
    
    // Initialize starting state
    moves[0] = (State){0, 0, 2, 2, false, false, "Start"};
    
    while (moveCount < MAX_MOVES) {
        State current = moves[moveCount];
        
        // Success condition
        if (current.hasBanana) {
            printf("\nSolution found in %d moves:\n", moveCount + 1);
            for (int i = 0; i <= moveCount; i++) {
                printf("Step %d: %s\n", i + 1, moves[i].move);
            }
            return;
        }
        
        State next = current;
        moveCount++;
        
        // If monkey has reached banana position while on box
        if (current.onBox && current.boxX == bananaX && current.boxY == bananaY) {
            next.hasBanana = true;
            strcpy(next.move, "Grab banana");
            moves[moveCount] = next;
            continue;
        }
        
        // If monkey is at box position, can climb it
        if (current.monkeyX == current.boxX && current.monkeyY == current.boxY && !current.onBox) {
            next.onBox = true;
            strcpy(next.move, "Climb box");
            moves[moveCount] = next;
            continue;
        }
        
        // Move monkey (and box if on it) towards banana
        int newX = current.monkeyX;
        int newY = current.monkeyY;
        
        if (current.onBox) {
            // Move towards banana with box
            if (current.boxX < bananaX) newX++;
            else if (current.boxX > bananaX) newX--;
            if (current.boxY < bananaY) newY++;
            else if (current.boxY > bananaY) newY--;
        } else {
            // Move towards box
            if (current.monkeyX < current.boxX) newX++;
            else if (current.monkeyX > current.boxX) newX--;
            if (current.monkeyY < current.boxY) newY++;
            else if (current.monkeyY > current.boxY) newY--;
        }
        
        if (isValidMove(newX, newY)) {
            next.monkeyX = newX;
            next.monkeyY = newY;
            if (current.onBox) {
                next.boxX = newX;
                next.boxY = newY;
                sprintf(next.move, "Move with box to (%d,%d)", newX, newY);
            } else {
                sprintf(next.move, "Move to (%d,%d)", newX, newY);
            }
            moves[moveCount] = next;
        }
    }
    
    printf("No solution found within %d moves\n", MAX_MOVES);
}

int main() {
    int bananaX = 4, bananaY = 4;  // Banana position
    printf("Monkey and Banana Problem\n");
    printf("Monkey starts at (0,0), Box at (2,2), Banana at (4,4)\n");
    solvePuzzle(bananaX, bananaY);
    return 0;
}
