/**
 * @author Turan
 * @date 19.8.2025
 */

#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>

#include "startMenu.h"
#include "game.h"

#define WIDTH 9
#define HEIGHT 9

/**
 * @purpose Initializing
 *
 * @return true if everything went good
 */
bool initialize();

/**
 * @purpose draws the Map
 */
void drawMap();

/**
 * @purpose free memory
 */
void destroy();


int main(void) {
  if (!initialize()) {
    perror("Failed to initialize");
  }

  srand(time(NULL));

  GameDiff diff; // game difficulty

  menu(&diff);
  game(diff);

  destroy();
  return 0;
}

bool
initialize() {
  initscr();

  start_color(); // needed for colors
  init_pair(1, COLOR_RED, COLOR_BLACK);   // foreground red, background black
  init_pair(2, COLOR_WHITE, COLOR_BLACK); // foreground white, background black

  cbreak(); // disable line buffering
  noecho(); // no echoing of typed characters
  keypad(stdscr, true); // enable arrow keys and other
  curs_set(0); // hide cursor

  return true;
}


void destroy() {
  endwin();
}
