/**
 * @author Turan
 * @date 20.8.2025
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>

#include "startMenu.h"

typedef struct startMenu{
  bool quit; // true if user pressed exit on the start menu
  GameDiff difficulty; // which difficulty the player wants to play on
};

// GAMEMODES
#define EASY_WIDTH 9
#define EASY_HEIGHT 9
#define EASY_MINES_AMOUNT 10

#define MEDIUM_WIDTH 16
#define MEDIUM_HEIGHT 16
#define MEDIUM_MINES_AMOUNT 40

#define HARD_WIDTH 30
#define HARD_HEIGHT 16
#define HARD_MINES_AMOUNT 99

// KEYS
#define KEY_SPACE ' '

typedef struct Cell {
  bool isRevealed; // If the cell revealed or not
  bool isBomb; // If the cell is a bomb
  int num; // Number of bombs in its radius.
}Cell;

/**
 *
 */
void drawGrid(int width, int height, int cursorX, int cursorY);

/**
 *
 * @param diff
 * @param width
 * @param height
 * @return
 */
Cell* allocGameGrid(GameDiff diff, int* width, int* height);

/**
 *
 * @param grid
 */
void initGameGrid(Cell* grid, GameDiff diff, int width, int height);

/**
 *
 * @param cursorX
 * @param cursorY
 */
bool getInput(int* cursorX, int* cursorY, int width, int height);

/**
 *
 * @param diff
 */
void game(GameDiff diff);


#endif //GAME_H