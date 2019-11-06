/*@erhanonal
Erhan Önal
Date: 22.04.2019 */

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

/**
        Structure for symbol
        @type type Type of the Symbol
        @centerRow Row indes of the center
        @centerCol Column index of the center
        @length Length of the symbol
*/

struct Symbol {
  char type;
  int centerRow, centerCol;
  int length;
};

/**
        Structure for move input
        @direction Direction of the move operation
        @row Row index of the symbol moved
        @col Column index of the symbol
        @distance Distance of the move operation
*/

struct MoveInput {
  char direction[3];
  int row, col, distance;
};

/**
        Fils the grid with an empty symbol
        @param gridRow Number of Rows in the grid
        @param gridCol Number of Columns in the grid
*/

void fillGrid(int gridRow, int gridCol, Symbol **grid) {

  Symbol emptySymbol;
  emptySymbol.type = '.';
  emptySymbol.centerRow = 1;
  emptySymbol.centerCol = 1;
  emptySymbol.length = 1;

  for (int i = 0; i < gridRow; i++)
    for (int j = 0; j < gridCol; j++)
      grid[i][j] = emptySymbol;
}

/**
        Checks if the symbol fits in the grid
        @param symbol Checked symbol
        @param gridRow Number of Rows in the grid
        @param gridCol Number of Columns in the grid
        @return result Returns true if the symbol fits, retunrs false if it
   doesn't

*/

bool BorderCheck(Symbol symbol, int gridRow, int gridCol) {
  bool result;
  switch (symbol.type) {
  case '+':
  case 'x':
  case '/':
    result = (symbol.centerRow - symbol.length > 0 &&
              symbol.centerRow + symbol.length <= gridRow &&
              symbol.centerCol - symbol.length > 0 &&
              symbol.centerCol + symbol.length <= gridCol);
    break;
  case '-':
    result = (symbol.centerCol - symbol.length > 0 &&
              symbol.centerCol + symbol.length <= gridCol);
    break;
  default:
    cout << "Wrong Symbol";
    result = false;
    break;
  }
  return result;
}

/**
        Checks if the symbol conflicts with an already placed symbol
        @param symbol The checked symbol
        @param gridRow Number of Rows in the grid
        @param gridCol Number of Columns in the grid
        @param grid Pointer to the grid
        @return Returns true if there is no conflict, returns false if there is
   a conflict
*/

bool ConflictCheck(Symbol symbol, int gridRow, int gridCol, Symbol **grid) {
  bool result = true;
  switch (symbol.type) {
  case '+':
    for (int i = 0; i <= symbol.length; i++) {
      if (symbol.centerRow + i <= gridRow) {
        if (grid[symbol.centerRow + i - 1][symbol.centerCol - 1].type != '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerRow - i > 0) {
        if (grid[symbol.centerRow - i - 1][symbol.centerCol - 1].type != '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerCol + i <= gridCol) {
        if (grid[symbol.centerRow - 1][symbol.centerCol + i - 1].type != '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerCol - i > 0) {
        if (grid[symbol.centerRow - 1][symbol.centerCol - i - 1].type != '.') {
          result = false;
          break;
        }
      }
    }
    break;

  case '-':
    for (int i = 0; i <= symbol.length; i++) {
      if (symbol.centerCol + i <= gridCol) {
        if (grid[symbol.centerRow - 1][symbol.centerCol + i - 1].type != '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerCol - i > 0) {
        if (grid[symbol.centerRow - 1][symbol.centerCol - i - 1].type != '.') {
          result = false;
          break;
        }
      }
    }
    break;

  case 'x':
    for (int i = 0; i <= symbol.length; i++) {
      if (symbol.centerRow + i <= gridRow && symbol.centerCol + i <= gridCol) {
        if (grid[symbol.centerRow + i - 1][symbol.centerCol + i - 1].type !=
            '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerRow + i <= gridRow && symbol.centerCol - i > 0) {
        if (grid[symbol.centerRow + i - 1][symbol.centerCol - i - 1].type !=
            '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerRow - i > 0 && symbol.centerCol + i <= gridCol) {
        if (grid[symbol.centerRow - i - 1][symbol.centerCol + i - 1].type !=
            '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerRow - i > 0 && symbol.centerCol - i > 0) {
        if (grid[symbol.centerRow - i - 1][symbol.centerCol - i - 1].type !=
            '.') {
          result = false;
          break;
        }
      }
    }
    break;
  case '/':
    for (int i = 0; i <= symbol.length; i++) {
      if (symbol.centerRow + i <= gridRow && symbol.centerCol - i > 0) {
        if (grid[symbol.centerRow + i - 1][symbol.centerCol - i - 1].type !=
            '.') {
          result = false;
          break;
        }
      }
      if (symbol.centerRow - i > 0 && symbol.centerCol + i <= gridCol) {
        if (grid[symbol.centerRow - i - 1][symbol.centerCol + i - 1].type !=
            '.') {
          result = false;
          break;
        }
      }
    }
    break;
  default:
    cout << "Wrong Type" << endl;
    break;
  }
  return result;
}

/**
        Adds the symbol to the grid
        @param symbol The added symbol
        @param grid Pointer to the grid
*/

void addSymbol(Symbol symbol, Symbol **grid) {
  switch (symbol.type) {
  case '+':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow + i - 1][symbol.centerCol - 1] = symbol;
      grid[symbol.centerRow - i - 1][symbol.centerCol - 1] = symbol;
      grid[symbol.centerRow - 1][symbol.centerCol + i - 1] = symbol;
      grid[symbol.centerRow - 1][symbol.centerCol - i - 1] = symbol;
    }
    break;
  case '-':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow - 1][symbol.centerCol + i - 1] = symbol;
      grid[symbol.centerRow - 1][symbol.centerCol - i - 1] = symbol;
    }
    break;
  case 'x':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow + i - 1][symbol.centerCol + i - 1] = symbol;
      grid[symbol.centerRow + i - 1][symbol.centerCol - i - 1] = symbol;
      grid[symbol.centerRow - i - 1][symbol.centerCol + i - 1] = symbol;
      grid[symbol.centerRow - i - 1][symbol.centerCol - i - 1] = symbol;
    }
    break;
  case '/':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow - i - 1][symbol.centerCol + i - 1] = symbol;
      grid[symbol.centerRow + i - 1][symbol.centerCol - i - 1] = symbol;
    }
    break;
  default:
    cout << "Wrong Symbol" << endl;
    break;
  }
}

/**
        Deletes a symbol
        @param symbol Deleted symbol
        @param grid Pointer to the grid
*/

void deleteSymbol(Symbol symbol, Symbol **grid) {

  Symbol emptySymbol;
  emptySymbol.type = '.';
  emptySymbol.centerRow = 1;
  emptySymbol.centerCol = 1;
  emptySymbol.length = 1;

  switch (symbol.type) {
  case '+':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow + i - 1][symbol.centerCol - 1] = emptySymbol;
      grid[symbol.centerRow - i - 1][symbol.centerCol - 1] = emptySymbol;
      grid[symbol.centerRow - 1][symbol.centerCol + i - 1] = emptySymbol;
      grid[symbol.centerRow - 1][symbol.centerCol - i - 1] = emptySymbol;
    }
    break;
  case '-':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow - 1][symbol.centerCol + i - 1] = emptySymbol;
      grid[symbol.centerRow - 1][symbol.centerCol - i - 1] = emptySymbol;
    }
    break;
  case 'x':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow + i - 1][symbol.centerCol + i - 1] = emptySymbol;
      grid[symbol.centerRow + i - 1][symbol.centerCol - i - 1] = emptySymbol;
      grid[symbol.centerRow - i - 1][symbol.centerCol + i - 1] = emptySymbol;
      grid[symbol.centerRow - i - 1][symbol.centerCol - i - 1] = emptySymbol;
    }
    break;
  case '/':
    for (int i = 0; i <= symbol.length; i++) {
      grid[symbol.centerRow - i - 1][symbol.centerCol + i - 1] = emptySymbol;
      grid[symbol.centerRow + i - 1][symbol.centerCol - i - 1] = emptySymbol;
    }
    break;
  default:
    cout << "Wrong Symbol-delete" << endl;
    break;
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Wrong Arguments";
    return EXIT_FAILURE;
  }

  FILE *gridTxt;
  gridTxt = fopen(argv[1], "r");
  if (!gridTxt) {
    cout << "Could not open grid.txt";
  }

  int gridRow, gridCol;
  fscanf(gridTxt, "%d %d", &gridRow, &gridCol);

  Symbol **grid;
  grid = new Symbol *[gridRow];
  for (int i = 0; i < gridRow; i++) {
    grid[i] = new Symbol[gridCol];
  }

  cout << "A grid is created: " << gridRow << " " << gridCol << endl;
  fillGrid(gridRow, gridCol, grid);

  Symbol inputSymbol;

  while (fscanf(gridTxt, " %c %d %d %d", &inputSymbol.type,
                &inputSymbol.centerRow, &inputSymbol.centerCol,
                &inputSymbol.length) == 4) {

    bool add = true;
    if (!BorderCheck(inputSymbol, gridRow, gridCol)) {
      cout << "BORDER ERROR: Operator " << inputSymbol.type << " with size "
           << inputSymbol.length << " can not be placed on ("
           << inputSymbol.centerRow << "," << inputSymbol.centerCol << ")."
           << endl;
      add = false;
    }
    if (!ConflictCheck(inputSymbol, gridRow, gridCol, grid)) {
      cout << "CONFLICT ERROR: Operator " << inputSymbol.type << " with size "
           << inputSymbol.length << " can not be placed on ("
           << inputSymbol.centerRow << "," << inputSymbol.centerCol << ")."
           << endl;
      add = false;
    }
    if (add) {
      addSymbol(inputSymbol, grid);
      cout << "SUCCESS: Operator " << inputSymbol.type << " with size "
           << inputSymbol.length << " is placed on (" << inputSymbol.centerRow
           << "," << inputSymbol.centerCol << ")." << endl;
    }
  }

  fclose(gridTxt);

  FILE *instructionsTxt;
  instructionsTxt = fopen(argv[2], "r");
  if (!instructionsTxt) {
    cout << "Could not open instuctions.txt" << endl;
  }

  MoveInput moveInput;

  while (fscanf(instructionsTxt, " %s %d %d %d",(char*)&moveInput.direction,
                &moveInput.row, &moveInput.col, &moveInput.distance) == 4) {
    Symbol originalSymbol;
    Symbol movedSymbol;
    originalSymbol.centerRow =
        grid[moveInput.row - 1][moveInput.col - 1].centerRow;
    originalSymbol.centerCol =
        grid[moveInput.row - 1][moveInput.col - 1].centerCol;
    originalSymbol.type = grid[moveInput.row - 1][moveInput.col - 1].type;
    originalSymbol.length = grid[moveInput.row - 1][moveInput.col - 1].length;
    movedSymbol.type = originalSymbol.type;
    movedSymbol.length = originalSymbol.length;

    if (!strcmp(moveInput.direction, "MVR")) {
      movedSymbol.centerRow = originalSymbol.centerRow;
      movedSymbol.centerCol = originalSymbol.centerCol + moveInput.distance;
    } else if (!strcmp(moveInput.direction, "MVL")) {
      movedSymbol.centerRow = originalSymbol.centerRow;
      movedSymbol.centerCol = originalSymbol.centerCol - moveInput.distance;
    } else if (!strcmp(moveInput.direction, "MVU")) {
      movedSymbol.centerRow = originalSymbol.centerRow - moveInput.distance;
      movedSymbol.centerCol = originalSymbol.centerCol;
    } else if (!strcmp(moveInput.direction, "MVD")) {
      movedSymbol.centerRow = originalSymbol.centerRow + moveInput.distance;
      movedSymbol.centerCol = originalSymbol.centerCol;
    } else {
      cout << "Wrong operation" << endl;
    }

    bool move = true;

    deleteSymbol(originalSymbol, grid);

    if (!BorderCheck(movedSymbol, gridRow, gridCol)) {
      cout << "BORDER ERROR: " << movedSymbol.type << " can not be moved from ("
           << originalSymbol.centerRow << "," << originalSymbol.centerCol
           << ") to (" << movedSymbol.centerRow << "," << movedSymbol.centerCol
           << ")." << endl;
      move = false;
    }

    if (!ConflictCheck(movedSymbol, gridRow, gridCol, grid)) {
      cout << "CONFLICT ERROR: " << movedSymbol.type
           << " can not be moved from (" << originalSymbol.centerRow << ","
           << originalSymbol.centerCol << ") to (" << movedSymbol.centerRow
           << "," << movedSymbol.centerCol << ")." << endl;
      move = false;
    }

    if (!move) {
      addSymbol(originalSymbol, grid);
    }

    else {

      addSymbol(movedSymbol, grid);
      cout << "SUCCESS: " << movedSymbol.type << " moved from ("
           << originalSymbol.centerRow << "," << originalSymbol.centerCol
           << ") to (" << movedSymbol.centerRow << "," << movedSymbol.centerCol
           << ")." << endl;
    }
  }

  fclose(instructionsTxt);

  return EXIT_SUCCESS;
}
