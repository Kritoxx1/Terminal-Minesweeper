/**
 * @author Turan
 * @date 20.8.2025
 */

#include "game.h"

void
drawGrid(const Cell* grid, const int width, const int height,
          const int cursorX, const int cursorY) {
  clear(); // clears the screen

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Cell c = grid[y * width + x]; // get current cell

      if (x == cursorX && y == cursorY) {
        attron(A_REVERSE); // highlight cursor
      }

      if (c.isRevealed) {
        if (c.isBomb) {
          mvaddch(y, x * 2, 'B'); // Bomb
        } else if (c.num > 0) {
          mvaddch(y, x * 2, '0' + c.num); // number
        } else {
          mvaddch(y, x * 2, ' '); // Empty
        }
      } else if (c.isFlagged) {
        mvaddch(y, x * 2, 'F'); // Place flag
      } else {
        mvaddch(y, x * 2, '#'); // hidden
      }

      if (x == cursorX && y == cursorY) {
        attroff(A_REVERSE);
      }

    }
  }
  refresh();
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
    default:
      perror("Error");
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
          if (nx >= 0 && nx < width && ny >= 0 && ny < height) { // Check if it is still in the grid
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
getInput(const Cell* grid, int* cursorX, int* cursorY,
          const int width, const int height) {
  int ch = getch();

  Cell* c = &grid[*cursorY * width + *cursorX];

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
      if (!c->isRevealed) {
        c->isRevealed = true;
        if (c->isBomb) {
          return false; // game over
        }
      }
      break;
    case KEY_LF:
    case KEY_FF: // place flag
      if (c->isFlagged) {
        c->isFlagged = false; // Remove flag if it is already there
      } else {
        c->isFlagged = true; // place flag
        printf("Placed Flag");
      }
      break;
    case 'q': // quit
      return false;
    default:
      // No default cuz would be annoying ;P
      break;
  }
  return true;
}

void
game(GameDiff diff) {
  int width;
  int height;
  Cell* grid = allocGameGrid(diff, &width, &height);

  int cursorX = 0, cursorY = 0;
  getInput(grid, &cursorX, &cursorY, width, height);

  /* Draw Grid */
  drawGrid(grid, width, height, cursorX, cursorY);

  /* Finally initializing the game grid */
  initGameGrid(grid, diff, width, height);

  bool running = true;
  while (running) {
    drawGrid(grid, width, height, cursorX, cursorY);
    running = getInput(grid, &cursorX, &cursorY, width, height);
  }

  free(grid);
}
