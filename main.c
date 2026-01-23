/**
 * @author Turan
 * @date 19.8.2025
 */

#include <stdbool.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "startMenu.h"
#include "gameOverMenu.h"
#include "game.h"
#include "winMenu.h"

#define WIDTH 9
#define HEIGHT 9

/**
 * @brief Initializing mmwmwmwmw
 */
void initialize();

/**
 * @brief free memory
 */
void destroy();


int main(void) {
  initialize();
  srand(time(NULL));

  GameDiff diff; // game difficulty

  bool gameShouldEnd = false;

  menu(&diff, &gameShouldEnd);

  while (!gameShouldEnd) {

    bool playAgain = false; // true if Yes, false if No
    if (!game(diff)) {
      sleep(2);
      playAgain = gameOverMenu();
    }
    else {
      sleep(2);
      playAgain = winMenu();
    }

    if (!playAgain) {
      menu(&diff, &gameShouldEnd); // exit loop
    }
  }

  destroy();
  return 0;
}

void
initialize() {
  initscr();

  start_color(); // needed for colors

  init_pair(1, COLOR_RED, COLOR_BLACK); // 3, F
  init_pair(2, COLOR_WHITE, COLOR_BLACK); // 7
  init_pair(3, COLOR_BLUE, COLOR_BLACK); // 1
  init_pair(4, 19, COLOR_BLACK); // 4 (navy blue)
  init_pair(5, COLOR_GREEN, COLOR_BLACK); // 2 (green)
  init_pair(6, 130, COLOR_BLACK); // 5 (brown)
  init_pair(7, COLOR_CYAN, COLOR_BLACK); // 6
  init_pair(8, 196, COLOR_BLACK); // bright red



  cbreak(); // disable line buffering
  noecho(); // no echoing of typed characters
  keypad(stdscr, true); // enable arrow keys and other
  curs_set(0); // hide cursor

}

void
destroy() {
  endwin();
}
