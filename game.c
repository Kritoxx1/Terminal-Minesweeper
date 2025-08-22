/**
 * @author Turan
 * @date 20.8.2025
 */

#include "game.h"

void
drawGrid(int width, int height, int cursorX, int cursorY) {
  clear(); // clears the screen

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (x == cursorX && y == cursorY) {
        attron(A_REVERSE); // highlight
        mvaddch(y, x * 2, '#');
        attroff(A_REVERSE);
        refresh();
      } else {
        mvaddch(y, x * 2, '#');
        refresh();
      }
    }
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
initGameGrid(Cell* grid, GameDiff diff, int width, int height) {
  memset(grid, 0, width * height * sizeof(Cell)); // Init everything to 0.

  int mineAmount;
  switch (diff) {
    case EASY:
      mineAmount = EASY_MINES_AMOUNT;
      break;
    case MEDIUM:
      mineAmount = MEDIUM_MINES_AMOUNT;
      break;
    case HARD:
      mineAmount = HARD_MINES_AMOUNT;
      break;
    case CUSTOM:
      // soon.
      break;
  }

  /* Placing mines */
  int placed = 0;
  while (placed < mineAmount) {
    int rx = rand() % width;
    int ry = rand() % height;
    Cell* c = &grid[ry * width + rx];
    if (!c->isBomb) { // avoiding duplicates
      c->isBomb = true;
      placed++;
    }
  }

  /* Calculate count of mines around a cell */
  int dx[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
  int dy[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Cell* c = &grid[y * width + x];
      if (c->isBomb) {
        for (int d = 0; d < 8; d++) {
          int nx = x + dx[d];
          int ny = y + dy[d];
          if (nx >= 0 && nx < width && ny >= 0 && ny < height) { // Check if It's still in the grid
            Cell* n = &grid[ny * width + nx];
            if (!n->isBomb) {
              n->num++;
            }
          }
        }
      }
    }
  }

}

bool
getInput(int* cursorX, int* cursorY, int width, int height) {
  int ch = getch();
  switch (ch) {
    case KEY_UP:
      if (*cursorY > 0) (*cursorY)--;
      break;
    case KEY_DOWN:
      if (*cursorY < height - 1) (*cursorY)++;
      break;
    case KEY_LEFT:
      if (*cursorX > 0) (*cursorX)--;
      break;
    case KEY_RIGHT:
      if (*cursorX < width - 1) (*cursorX)++;
      break;
    case KEY_SPACE: // reveal Cell

      break;
    case 'q': // quit
      return false;
  }
  return true;
}

void
game(GameDiff diff) {
  int width;
  int height;
  Cell* grid = allocGameGrid(diff, &width, &height);

  int cursorX = 0, cursorY = 0;
  getInput(&cursorX, &cursorY, width, height);

  /* Draw Grid */
  drawGrid(width, height, cursorX, cursorY);

  /* Finally initializing the game grid */
  initGameGrid(grid, diff, width, height);

  bool running = true;
  while (running) {
    drawGrid(width, height, cursorX, cursorY);
    running = getInput(&cursorX, &cursorY, width, height);
  }

  free(grid);
}
