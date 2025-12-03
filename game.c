/**
 * @author Turan
 * @date 20.8.2025
 */

#include "game.h"

bool
floodReveal(Cell* grid, int x, int y, int width, int height) {
  /* out of bound check */
  if (x < 0 || x >= width || y < 0 || y >= height)
    return false;

  Cell* c = &grid[y * width + x];

  if (c->isRevealed || c->isFlagged)
    return false;

  // reveal the cell
  c->isRevealed = true;
  revealedCount--;

  if(c->isBomb)
    return true;

  // if not empty stop
  if (c->num > 0)
    return false;


  // else expand to all neighbors
  int dx[8] = {-1,-1,-1,0,0,1,1,1};
  int dy[8] = {-1,0,1,-1,1,-1,0,1};
  for (int i = 0; i < 8; i++) {
    if(floodReveal(grid, x + dx[i], y + dy[i], width, height))
      break;
  }
}

bool
revealLeftOverCells(Cell* grid, int x, int y, int width, int height) {
  if (x < 0 || x >= width || y < 0 || y >= height)
    return true;

  // Current Cell where the player Clicked
  Cell* c = &grid[y * width + x];

  int numOfFlagsNeeded = c->num;

  int dx[8] = {-1,-1,-1,0,0,1,1,1};
  int dy[8] = {-1,0,1,-1,1,-1,0,1};

  int flags = 0;
  for (int i = 0; i < 8; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx < 0 || nx >= width || ny < 0 || ny >= height) continue;

    Cell* neighbor = &grid[ny * width + nx];
    if (!neighbor->isRevealed && neighbor->isFlagged) flags++;
  }

  if (flags >= numOfFlagsNeeded) {
    for (int i = 0; i < 8; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (nx < 0 || nx >= width || ny < 0 || ny >= height) continue;

      Cell* neighbor = &grid[ny * width + nx];

      if (neighbor->isRevealed || neighbor->isFlagged) continue;

      if (neighbor->num == 0) {
        floodReveal(grid, nx, ny, width, height);
      } else {
        if (neighbor->isBomb) {
          return false;
        }
        neighbor->isRevealed = true;
        revealedCount--;
      }

    }
  }

  return true;
}

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
          switch (c.num) {
            case 1:
              attron(COLOR_PAIR(3)); // Blue
              mvaddch(y, x * 2, '0' + c.num);
              attroff(COLOR_PAIR(3));
              break;
            case 2:
              attron(COLOR_PAIR(5)); // Green
              mvaddch(y, x * 2, '0' + c.num);
              attroff(COLOR_PAIR(5));
              break;
            case 3:
              attron(COLOR_PAIR(1)); // Red
              mvaddch(y, x * 2, '0' + c.num);
              attroff(COLOR_PAIR(1));
              break;
            case 4:
              attron(COLOR_PAIR(4)); // Magenta
              mvaddch(y, x * 2, '0' + c.num);
              attroff(COLOR_PAIR(4));
              break;
            case 5:
              attron(COLOR_PAIR(6)); // Yellow
              mvaddch(y, x * 2, '0' + c.num);
              attroff(COLOR_PAIR(6));
              break;
            case 6:
              attron(COLOR_PAIR(7)); // Cyan
              mvaddch(y, x * 2, '0' + c.num);
              attroff(COLOR_PAIR(7));
              break;
            case 7:
              attron(COLOR_PAIR(2)); // White ... Sadly no more colors
              mvaddch(y, x * 2, '0' + c.num);
              attroff(COLOR_PAIR(2));
              break;
          }


        } else {
          mvaddch(y, x * 2, ' '); // Empty
        }
      } else if (c.isFlagged) {
        attron(COLOR_PAIR(8)); // turn on Red
        mvaddch(y, x * 2, 'F'); // Place flag
        attroff(COLOR_PAIR(8));
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

  // allocate memory for the grid
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

  // How many free cells there are.
  revealedCount = (width * height) - mineAmount;

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
    case KEY_SPACE: // reveal
      if (!c->isRevealed && !c->isFlagged) {
        if (c->isBomb) {
          return false;
        } else if (c->num == 0) {
          floodReveal(grid, *cursorX, *cursorY, width, height);
        } else {
          c->isRevealed = true;
          revealedCount--;
        }
      } else if (c->isRevealed && c->num != 0) {
        if (!revealLeftOverCells(grid, *cursorX, *cursorY, width, height)) {
          // Mine revealed -> Game Over
          return false;
        }
      }

      break;
    case KEY_LF:
    case KEY_FF: // place flag
      if (c->isFlagged) {
        c->isFlagged = false; // Remove flag if it is already there
      } else {
        c->isFlagged = true; // place flag
      }
      break;
    case 'Q':
    case 'q': // quit
      return false;
    case 'D':
    case 'd': // DEBUG: print revealedCount
      clear();
      printw("REVEALEDCOUNT: %d", revealedCount);
      refresh();
      sleep(1);
      break;
    default:
      // No default cuz would be annoying ;P
      break;
  }
  return true;
}

bool
winChecker() {
  if (!revealedCount) {
    return true;
  }
  return false;
}

bool
game(GameDiff diff) {
  int width;
  int height;
  Cell* grid = allocGameGrid(diff, &width, &height);

  int cursorX = 0, cursorY = 0;

  /* Draw Grid */
  drawGrid(grid, width, height, cursorX, cursorY);

  bool running = true;
  running = getInput(grid, &cursorX, &cursorY, width, height);

  /* Finally initializing the game grid */
  initGameGrid(grid, diff, width, height);
  
  bool win = false;
  while (running) {
    drawGrid(grid, width, height, cursorX, cursorY);
    running = getInput(grid, &cursorX, &cursorY, width, height);
    win = winChecker();
    if (win) running = false;
  }
  
  /* Draw grid one last time */
  drawGrid(grid, width, height, cursorX, cursorY);

  sleep(1);
   
  free(grid);
  return win; 
}
