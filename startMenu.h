/**
 * @author Turan
 * @date 19.08.2025
*/

#ifndef STARTMENU_H
#define STARTMENU_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* MENU OPTION */
typedef enum GameDiff {
  EASY,
  MEDIUM,
  HARD,
  CUSTOM, // Adding later...
  ERROR = -1,
  AMOUNT_OF_OPTIONS = 4,
}GameDiff;

typedef enum menuOptions {
  PLAY,
  OPTIONS,
  EXIT,
  AMOUNT_OF_MENU_OPTIONS = 3,
}menuOptions;

/**
 *
 * @return Which mode the player wants (easy, medium, hard, custom)
 */
GameDiff playMenu();


/**
 * @purpose shows a beautiful start menu when u start the game
 *          where the user can choose between different difficulties.
 *
 * @param difficulty_var ... The variable that
 *
 * @return ...
 */
void menu(GameDiff* difficulty_var, bool* gameEndVar);

#endif //STARTMENU_H
