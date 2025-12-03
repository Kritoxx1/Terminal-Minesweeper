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
#define KEY_FF 'F' // (F key)
#define KEY_LF 'f' // (f key)

// Variables
static int revealedCount;

typedef struct Cell {
  bool isRevealed; // If the cell revealed or not
  bool isBomb; // If the cell is a bomb
  bool isFlagged; // If the cell got a flag
  int num; // Number of bombs in its radius.
}Cell;

/**
 * @brief ... Draws the grid to the terminal
 *
 * @param grid
 * @param width
 * @param height
 * @param cursorX
 * @param cursorY
 */
void drawGrid(const Cell* grid, const int width, const int height,
              const int cursorX, const int cursorY);

/**
 * @brief ... Allocate memory for the grid
 *
 * @param diff
 * @param width
 * @param height
 * @return
 */
Cell* allocGameGrid(GameDiff diff, int* width, int* height);

/**
 * @brief ... Fills the Grid with information
 *
 * @param grid
 */
void initGameGrid(Cell* grid, GameDiff diff, int width, int height);

/**
 * @brief ... Main input getter for the game controll
 *
 * @param cursorX
 * @param cursorY
 */
bool getInput(const Cell* grid, int* cursorX, int* cursorY, const int width, const int height);

/**
 * @brief ... Chain reaction of revealing empty celss
 *
 * @param grid
 * @param x
 * @param y
 * @param width
 * @param height
 */
bool floodReveal(Cell* grid, int x, int y, int width, int height);

/**
 * @brief ... 
 *
 * @param grid
 * @param x
 * @param y
 * @param width
 * @param height
 * @return
 */
bool revealLeftOverCells(Cell* grid, int x, int y, int width, int height);

/**
 * @brief ... Checks for win
 * 
 * @param grid
 * @param diff
 * @return
 */
bool winChecker();

/**
 * @brief ... Main game loop
 * @param diff
 */
bool game(GameDiff diff);


#endif //GAME_H
