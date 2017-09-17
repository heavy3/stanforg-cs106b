// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;

const bool LIVE = true;
const bool DIE = false;

// logic
void introduction();
void display(Grid<bool> &grid);
Grid<bool> clone(Grid<bool> &grid);
int neighbors(Grid<bool> &grid, int r, int c, bool wrap);
void tick(Grid<bool> &grid, bool wrap);

// helper function, return true if that position have living cells
bool topLeft(Grid<bool> &grid, int r, int c, bool wrap);
bool top(Grid<bool> &grid, int r, int c, bool wrap);
bool topRight(Grid<bool> &grid, int r, int c, bool wrap);
bool right(Grid<bool> &grid, int r, int c, bool wrap);
bool bottomRight(Grid<bool> &grid, int r, int c, bool wrap);
bool bottom(Grid<bool> &grid, int r, int c, bool wrap);
bool bottomLeft(Grid<bool> &grid, int r, int c, bool wrap);
bool left(Grid<bool> &grid, int r, int c, bool wrap);

int main() {

    // introduce abt game of life
    introduction();

    ifstream stream;
    promptUserForFile(stream, "Grid input file name?", "Unable to open that file.  Try again.");

    string buffer;

    // get row
    getline(stream, buffer);
    int row = stringToInteger(buffer);

    // get column
    getline(stream, buffer);
    int col = stringToInteger(buffer);

    Grid<bool> culture(row, col);

    // init grid value from file
    for (int r = 0; r < row; r++) {
        getline(stream, buffer);
        int len = buffer.size();
        for (int c = 0; c < len; c++) {
            if (buffer[c] == '-')
                culture[r][c] = false;
            else
                culture[r][c] = true;
        }
    }

    // close stream
    stream.close();

    // wrapping grid or not
    string shouldWrap = toLowerCase(getLine("Should the simulation wrap around the grid (y/n)?"));
    bool wrap = false;

    if (shouldWrap == "y")
        wrap = true;

    display(culture);

    // start the simulation
    while (true) {
        string command = toLowerCase(getLine("a)nimate, t)ick, q)uit?"));

        if (command == "a") {
            int frame = getInteger("How many frames?", "Illegal integer format. Try again.");
            for (int i = 0; i < frame; i++) {
                tick(culture, wrap);
                pause(50);
                clearConsole();
                display(culture);
            }

        } else if (command == "t") {
            tick(culture, wrap);
            display(culture);
        } else if (command == "q") {
            break;
        } else {
            cout << "Invalid choice; please try again." << endl;
        }
    }

    // good bye
    cout << "Have a nice Life!" << endl;
    return 0;
}

// print introduction statement
void introduction() {
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies.\n" << endl;
}

// display the grid in pretty form
void display(Grid<bool> &grid) {
    int rows = grid.numRows(),
        cols = grid.numCols();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == false)
                cout << '-';
            else
                cout << 'X';
        }
        cout << endl;
    }
}

// make a clone of grid
Grid<bool> clone(Grid<bool> &grid) {
    int rows = grid.numRows(),
        cols = grid.numCols();

    Grid<bool> temp(rows, cols);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            temp[r][c] = grid[r][c];
        }
    }
    return temp;
}

// return the number of neighbor for (r, c) grid with wrapping option
int neighbors(Grid<bool> &grid, int r, int c, bool wrap) {
    if (r > grid.numRows() || c > grid.numCols())
        return 0;
    int count = 0;

    if (topLeft(grid, r, c, wrap)) count++;
    if (top(grid, r, c, wrap)) count++;
    if (topRight(grid, r, c, wrap)) count++;
    if (right(grid, r, c, wrap)) count++;
    if (bottomRight(grid, r, c, wrap)) count++;
    if (bottom(grid, r, c, wrap)) count++;
    if (bottomLeft(grid, r, c, wrap)) count++;
    if (left(grid, r, c, wrap)) count++;

    return count;
}

void tick(Grid<bool> &grid, bool wrap) {
    Grid<bool> temp = clone(grid);

    int rows = grid.numRows(),
        cols = grid.numCols();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int around = neighbors(grid, r, c, wrap);

            if (around <= 1 || around >= 4) {
                temp[r][c] = DIE;
            } else if (around == 3) {
                temp[r][c] = LIVE;
            }
        }
    }
    grid = temp;
}

bool topLeft(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        r = ((r - 1) + grid.numRows()) % grid.numRows();
        c = ((c - 1) + grid.numCols()) % grid.numCols();
    } else {
        r = r - 1;
        c = c - 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}

bool top(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        r = ((r - 1) + grid.numRows()) % grid.numRows();
    } else {
        r = r - 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}

bool topRight(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        r = ((r - 1) + grid.numRows()) % grid.numRows();
        c = ((c + 1) + grid.numCols()) % grid.numCols();
    } else {
        r = r - 1;
        c = c + 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}

bool right(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        c = ((c + 1) + grid.numCols()) % grid.numCols();
    } else {
        c = c + 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}

bool bottomRight(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        r = ((r + 1) + grid.numRows()) % grid.numRows();
        c = ((c + 1) + grid.numCols()) % grid.numCols();
    } else {
        r = r + 1;
        c = c + 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}

bool bottom(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        r = ((r + 1) + grid.numRows()) % grid.numRows();
    } else {
        r = r + 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}

bool bottomLeft(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        r = ((r + 1) + grid.numRows()) % grid.numRows();
        c = ((c - 1) + grid.numCols()) % grid.numCols();
    } else {
        r = r + 1;
        c = c - 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}

bool left(Grid<bool> &grid, int r, int c, bool wrap) {
    if (wrap) {
        c = ((c - 1) + grid.numCols()) % grid.numCols();
    } else {
        c = c - 1;
    }
    return grid.inBounds(r, c) && grid[r][c];
}
