/**
 * @author Turan
 * @date 25.8.2025
*/

#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "game.h"
#include "startMenu.h"

typedef enum gameOverOptions {
  YES = 0, // Play again
  NO = 1, // Don't play again
  GAME_OVER_AMOUNT_OF_OPTIONS = 2
}gameOverOptions;

bool gameOverMenu();

#endif
