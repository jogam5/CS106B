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
    GridLocation exit = {g.numRows()-1,  g.numCols()-1};

    if (path.peek() != exit) {
        error("path does not end at exit");
    }
    // TODO: check rest of path is valid (see writeup)
    // if find a problem, call error() to report
    // if all checks out, return true
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

    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
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
