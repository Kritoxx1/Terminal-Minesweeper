/*
 * @author Turan
 * @date 27.8.2025
*/

#include "startMenu.h"
#include "gameOverMenu.h"
#include "winMenu.h"

GameDiff
playMenu() {
  clear(); // clears the screen

  const char* options[] = {
    "Easy",
    "Medium",
    "Hard",
    "Custom"
  };

  short choice = 0;

  /**/
  while (true) {
    clear();

    for (int i = 0; i < AMOUNT_OF_OPTIONS; i++) {
      if (i == choice) {
        attron(COLOR_PAIR(1));  // red
        printw("*%3s*\n", options[i]);
        attroff(COLOR_PAIR(1)); // red
      } else {
        attron(COLOR_PAIR(2));  // white
        printw("%s\n", options[i]);
        attroff(COLOR_PAIR(2)); // white
      }
      refresh();
    }
    int key = getch();

    if (key == KEY_UP && choice != 0) { // Arrow up pressed
      choice-=1;
    } else if (key == KEY_DOWN && choice != AMOUNT_OF_OPTIONS - 1) { // Arrow down pressed
      choice+=1;
    } else if (key == '\n' || key == KEY_SPACE) { // Enter or space pressed
      break;
    }
  }

  switch (choice) {
    case EASY:
      return EASY;
    case MEDIUM:
      return MEDIUM;
    case HARD:
      return HARD;
    case CUSTOM:
      return CUSTOM;
    default:
      return ERROR;
  }
}

void
menu(GameDiff* difficulty_var, bool* gameEndVar) {
  const char *options[] = {
    "Play",
    "Options",
    "Exit"
  };

  int choice = 0; // cursor is at "Play"

  /* Start menu main loop */
  while (true) {
    clear(); // Clear screen after every loop.

    for (int i = 0; i < AMOUNT_OF_MENU_OPTIONS; i++) {
      if (i == choice) {
        attron(COLOR_PAIR(1));  // turn on red
        printw("[%9s]\n", options[i]);
        attroff(COLOR_PAIR(1)); // turn off red
      } else {
        attron(COLOR_PAIR(2));  // white
        printw("[%9s]\n", options[i]);
        attroff(COLOR_PAIR(2));
      }
      refresh();
    }

    int key = getch(); // get user input.

    if (key == KEY_UP && choice != 0) { // Arrow up pressed
      choice-=1;
    } else if (key == KEY_DOWN && choice != AMOUNT_OF_MENU_OPTIONS - 1) { // Arrow down pressed
      choice+=1;
    } else if (key == '\n' || key == KEY_SPACE) { // Enter or space pressed
      break;
    }
  } // exit while loop

  switch (choice) {
    case PLAY:
      *difficulty_var = playMenu();
      break;

    case OPTIONS:
      break;

    case EXIT:
      *gameEndVar = true;
      break;
  }
}

// ---------------------------------------------------
// GAMEOVER

// not done yet.
bool 
gameOverMenu() {
  // sleep(3);
  clear(); // clear the screen

  const char* options[] = {
    "Yes",
    "No"
  };
  short choice = 0;

  while (true) {
    clear();
    attron(COLOR_PAIR(8)); // bright red
    printw("You stepped on a mine!\n");
    attroff(COLOR_PAIR(8)); // bright red
    printw("Do you want to play again?\n");
    for (int i = 0; i < GAME_OVER_AMOUNT_OF_OPTIONS; i++) {
      if (i == choice) {
        attron(COLOR_PAIR(1)); // red
        printw("*%3s*\n", options[i]);
        attroff(COLOR_PAIR(1)); // red
      } else {
        attron(COLOR_PAIR(2));  // white
        printw("%s\n", options[i]);
        attroff(COLOR_PAIR(2)); // white
      }
      refresh();
    }

    int key = getch();
    if (key == KEY_UP && choice != 0) { // Arrow up pressed
      choice--;
    } else if (key == KEY_DOWN && choice != AMOUNT_OF_OPTIONS - 1) { // Arrow down pressed
      choice++;
    } else if (key == '\n' || key == KEY_SPACE) {// Enter or space pressed
      break;
    }
  }

  switch (choice) {
    case YES:
      return true;
    case NO:
      return false;
    default:
      // Idk what to put here.  
      break;
  }

  return NULL;
}

bool
winMenu() {
  clear(); // clear the screen

  const char* options[] = {
    "Yes",
    "No"
  };
  short choice = 0;

  while (true) {
    clear();
    attron(COLOR_PAIR(5)); // green
    printw("You won!\n");
    attroff(COLOR_PAIR(5)); // green
    printw("Do you want to play again?\n");
    for (int i = 0; i < GAME_OVER_AMOUNT_OF_OPTIONS; i++) {
      if (i == choice) {
        attron(COLOR_PAIR(1)); // red
        printw("*%3s*\n", options[i]);
        attroff(COLOR_PAIR(1)); // red
      } else {
        attron(COLOR_PAIR(2));  // white
        printw("%s\n", options[i]);
        attroff(COLOR_PAIR(2)); // white
      }
      refresh();
    }

    int key = getch();
    if (key == KEY_UP && choice != 0) { // Arrow up pressed
      choice--;
    } else if (key == KEY_DOWN && choice != AMOUNT_OF_OPTIONS - 1) { // Arrow down pressed
      choice++;
    } else if (key == '\n' || key == KEY_SPACE) {// Enter or space pressed
      break;
    }
  }
  
  switch (choice) {
    case YES:
      return true;
    case NO:
      return false;
    default:
      // same as in Gameover
      break;
  }

  return NULL;
}
