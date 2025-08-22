/**
 * @author Turan
 * @date 20.8.2025
 */

#include "game.h"

//void
//drawGrid() {
//  clear(); // clears the screen
//
//  for (int y = 0; y < HEIGHT; y++) {
//    for (int x = 0; x < WIDTH; x++) {
//      mvaddch(y, x * 2, '#');
//      refresh();
//    }
//  }
//}

void
gameLoop() {
  while (true) {
  }
}


Cell*
allocGameGrid(GameDiff diff, int* width, int* height) {
  switch (diff) {
    case EASY:
      *width = EASY_WIDTH;
      *height = EASY_HEIGHT;
      break;
    case MEDIUM:
      *width = MEDIUM_WIDTH;
      *height = MEDIUM_HEIGHT;
      break;
    case HARD:
      *width = HARD_WIDTH;
      *height = HARD_HEIGHT;
      break;
    case CUSTOM:
      // soon.
      break;
    default:
      perror("Start game went wrong!");
      break;
  }

  Cell *gameGrid = malloc((*width) * (*height) * sizeof(Cell));
  if (!gameGrid) {
    perror("malloc failed");
    exit(1);
  }

  return gameGrid;
}

void
initGameGrid(Cell* grid) {

}

void
game(GameDiff diff) {
  int width;
  int height;
  Cell* grid = allocGameGrid(diff, &width, &height);

  /* Finally initializing the game grid */
  initGameGrid(grid);


}
