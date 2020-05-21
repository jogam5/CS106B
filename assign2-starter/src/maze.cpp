// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "stack.h"
#include "vector.h"
#include "maze.h"
#include "mazegraphics.h"
#include "testing/SimpleTest.h"
using namespace std;

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
bool checkSolution(Grid<bool>& g, Stack<GridLocation> path)
{
    Stack<GridLocation> pathCopy = path;
    // peek() -  look at the entity at the top of the stack, but don’t remove it

    // TODO: check rest of path is valid (see writeup)
    // if find a problem, call error() to report
    // if all checks out, return true

    // 1. Path must start at the upper left corner
    // validEntryPath
    GridLocation startMaze = {0, 0};
    GridLocation startPath;
    while(!pathCopy.isEmpty()) {
        startPath = pathCopy.pop();
    }
    if (startPath != startMaze) {
        error("path does not start at the upper left corner");
    }

    // 2. Path must end at the lower right coerner
    // validExitPath
    GridLocation exit = {g.numRows()-1,  g.numCols()-1};
    if (path.peek() != exit) {
        error("path does not end at exit");
    }
    // 3. Each location in the path is within maze bounds
    // isWithinBounds
    int xBound = g.numRows()-1;
    int yBound = g.numCols()-1;
    pathCopy = path;
    while(!pathCopy.isEmpty()){
        GridLocation location = pathCopy.pop();
        if (location.row > xBound || location.col > yBound) {
            error("path is beyond the bounds of the maze");
        } else if (location.row < 0 || location.col < 0) {
            error("path is beyond the bounds of the maze");
        }
    }

    // 4. Each location in the path is an open corridor
    // isCorridor
    pathCopy = path;
    while(!pathCopy.isEmpty()) {
        GridLocation location = pathCopy.pop();
            if (!g[location]) {
                error("paths is not an open corridor");
            }
    }
    // 5. Each location is one cardinal step (N,S,E,W) from the next in path
    // isCardinalStep
    pathCopy = path;
    while(!pathCopy.isEmpty()) {
        GridLocation currentLocation = pathCopy.pop();
        if (!pathCopy.isEmpty()) {
            GridLocation nextLocation = pathCopy.peek();
            if ( abs(currentLocation.row - nextLocation.row) > 1 || abs(currentLocation.col - nextLocation.col) > 1 ) {
                error("the location is more than one cardinal steps from the next one");
            }
         }
    }
    // 6. The path contains no loops
    // hasNoLoops
    pathCopy = path;
    while(!pathCopy.isEmpty()) {
        GridLocation currentLocation = pathCopy.pop();
        if(!pathCopy.isEmpty()) {
            GridLocation nextLocation = pathCopy.peek();
            if ( nextLocation.row > currentLocation.row || nextLocation.col > currentLocation.col) {
                error("The path contains loops: a location appears more than once");
            }
        }
    }
    return true;    
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file. However, there are various malformed
 * inputs which it does not correctly handle. You are to add
 * complete error-checking so that the function is fully robust.
 * See writeup.
 */
bool readMazeFile(string filename, Grid<bool>& maze)
{
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines;
    readEntireFile(in, lines);
    string lastLine = lines.removeBack(); // last line is solution if present

    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    /* Error detection # 2: Check for discrepancies in the length of rows */
    for(int i = 0; i < lines.size(); i++) {
        int rowLength = lines[0].length();
        if ((int)lines[i].length() > rowLength || (int)lines[i].length() < rowLength ) {
            error("One or more rows have a different length.");
        }
    }

    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                /* Error detection # 1: Check for characters different from expected*/
                error("Invalid character for a maze.");
            }
        }
    }
    Stack<GridLocation> solution;
    istringstream istr(lastLine); // Stack read does its own error-checking
    if (istr >> solution) {// if successfully read
        return checkSolution(maze, solution);
    }
    return true; // else no solution; nothing more to check
 }

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Stack<GridLocation> solveMaze(Grid<bool>& maze)
{
    Stack<GridLocation> p;
    // TODO: your code here
    return p;
}

/* * * * * * Student Test Cases For checkSolution* * * * * */
STUDENT_TEST("Raise error: Path must start at the upper left corner") {
    Grid<bool> g = {{true, false}, {true, true}};
    Stack<GridLocation> not_begin_at_entry = { {1, 0}, {1, 1} };
    EXPECT_ERROR(checkSolution(g, not_begin_at_entry));
}

STUDENT_TEST("Raise error: Path must start at the upper left corner") {
    Grid<bool> g = {{true, false, false}, {true, true, false}, {true, true, true}};
    Stack<GridLocation> not_begin_at_entry = { {0, 1}, {1, 0}, {2, 0}, {2, 1}, {2, 2}};
    EXPECT_ERROR(checkSolution(g, not_begin_at_entry));
}

STUDENT_TEST("checkSolution on correct path") {
    Grid<bool> g = {{true, false, false}, {true, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}};
    EXPECT(checkSolution(g, soln));
}

STUDENT_TEST("Raise error: Path must be within bounds") {
    Grid<bool> g = {{true, false, false}, {true, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {1, 0}, {5, 0}, {2, 1}, {2, 2}};
    EXPECT_ERROR(checkSolution(g, soln));
}

STUDENT_TEST("Raise error: Path must be within bounds") {
    Grid<bool> g = {{true, false, false}, {true, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {-10, 0}, {1, 0}, {2, 1}, {2, 2}};
    EXPECT_ERROR(checkSolution(g, soln));
}

STUDENT_TEST("Raise error: Location in the path isn't an open corridor") {
    Grid<bool> g = {{true, false, false}, {false, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}};
    EXPECT_ERROR(checkSolution(g, soln));
}

STUDENT_TEST("The path contains only open corridors") {
    Grid<bool> g = {{true, false, false}, {true, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}};
    EXPECT(checkSolution(g, soln));
}

STUDENT_TEST("Raise error: A location in the path is more than one cardinal step ") {
    Grid<bool> g = {{true, false, false}, {false, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {2, 0}, {2, 0}, {2, 1}, {2, 2}};
    EXPECT_ERROR(checkSolution(g, soln));
}

STUDENT_TEST("Raise error: A location in the path is more than one cardinal step ") {
    Grid<bool> g = {{true, false, false}, {false, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {1, 0}, {2, 0}, {2, 2}, {2, 2}};
    EXPECT_ERROR(checkSolution(g, soln));
}

STUDENT_TEST("Each location in the path is one cardinal step from the next in the path") {
    Grid<bool> g = {{true, false, false}, {true, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}};
    EXPECT(checkSolution(g, soln));
}

STUDENT_TEST("Raise error: The path contains loops") {
    Grid<bool> g = {{true, false, false}, {false, true, false}, {true, true, true}};
    Stack<GridLocation> soln = { {0, 0}, {1, 0}, {0,0}, {1,0}, {2, 0}, {2, 2}, {2, 2}};
    EXPECT_ERROR(checkSolution(g, soln));
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test readMazeFile on valid file 2x2.maze") {
    Grid<bool> g;

    EXPECT(readMazeFile("res/2x2.maze", g));
}

PROVIDED_TEST("Test readMaze on valid file 5x7.maze") {
    Grid<bool> g;

    EXPECT(readMazeFile("res/5x7.maze", g));
}

PROVIDED_TEST("readMazeFile on nonexistent file should raise an error") {
    Grid<bool> g;

    EXPECT_ERROR(readMazeFile("res/nonexistent_file", g));
}

PROVIDED_TEST("readMazeFile on malformed file should raise an error") {
    Grid<bool> g;

    EXPECT_ERROR(readMazeFile("res/malformed.maze", g));
}

STUDENT_TEST("readMazeFile on malformed file with blank spaces should raise an error") {
    Grid<bool> g;
    EXPECT_ERROR(readMazeFile("res/malformed_1.maze", g));
}

STUDENT_TEST("readMazeFile on malformed file with numbers should raise an error") {
    Grid<bool> g;
    EXPECT_ERROR(readMazeFile("res/malformed_2.maze", g));
}

STUDENT_TEST("readMazeFile on different row sizes should raise an error") {
    Grid<bool> g;
    EXPECT_ERROR(readMazeFile("res/errorSize3x3.maze", g));
}

STUDENT_TEST("readMazeFile on different row sizes should raise an error") {
    Grid<bool> g;
    EXPECT_ERROR(readMazeFile("res/errorSize4x4.maze", g));
}

PROVIDED_TEST("checkSolution on correct path") {
    Grid<bool> g = {{true, false}, {true, true}};
    Stack<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

    EXPECT(checkSolution(g, soln));
}

PROVIDED_TEST("checkSolution on invalid path should raise error") {
    Grid<bool> g = {{true, false}, {true, true}};
    Stack<GridLocation> not_end_at_exit = { {1, 0}, {0, 0} };
    Stack<GridLocation> not_begin_at_entry = { {1, 0}, {1, 1} };
    Stack<GridLocation> go_through_wall = { {0 ,0}, {0, 1}, {1, 1} };
    Stack<GridLocation> teleport = { {0 ,0}, {1, 1} };

    EXPECT_ERROR(checkSolution(g, not_end_at_exit));
    EXPECT_ERROR(checkSolution(g, not_begin_at_entry));
    EXPECT_ERROR(checkSolution(g, go_through_wall));
    EXPECT_ERROR(checkSolution(g, teleport));
}


PROVIDED_TEST("solveMaze on file 5x7") {
    Grid<bool> g;
    readMazeFile("res/5x7.maze", g);
    Stack<GridLocation> soln = solveMaze(g);

    EXPECT(checkSolution(g,soln));
}

PROVIDED_TEST("solveMaze on file 21x35") {
    Grid<bool> g;
    readMazeFile("res/21x35.maze", g);
    Stack<GridLocation> soln = solveMaze(g);

    EXPECT(checkSolution(g,soln));
}
