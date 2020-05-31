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
#include "queue.h"
#include "set.h"
#include "vector.h"
#include "maze.h"
#include "mazegraphics.h"
#include "testing/SimpleTest.h"
#include <chrono>
#include <thread>
using namespace std;

// This function reads in a Grid and a Stack, the former representing
// the maze and the latter the path to solve the maze. The goal of the
// function is to probe that the path follows certain rules so that
// the given path solves the maze

bool checkSolution(Grid<bool>& g, Stack<GridLocation> path)
{
    Stack<GridLocation> pathCopy = path;
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
    //Stack<GridLocation> teleport = { {0 ,0}, {1, 1} };
    pathCopy = path;
    cout << "sln:" << endl;
    cout << path << endl;
    while(!pathCopy.isEmpty()) {
        // a. check for diagonals
        // b. enforce vertical and horizontal movements
        GridLocation currentLocation = pathCopy.pop();
        if (!pathCopy.isEmpty()) {
            GridLocation nextLocation = pathCopy.peek();
            int deltaX = abs(currentLocation.row - nextLocation.row);
            int deltaY = abs(currentLocation.col - nextLocation.col);
            if (deltaX + deltaY != 1) {
                error("the location is more than one cardinal steps from the next one");
            }
         }
    }
    // 6. The path contains no loops
    // hasNoLoops
    pathCopy = path;
    Set<GridLocation> set;
    while(!pathCopy.isEmpty()) {
        GridLocation location = pathCopy.pop();
        if (set.contains(location)) {
            error("The path contains loops: the same location was visited before");
        } else {
            set.add(location);
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

// Helper 1
Stack<GridLocation> hasNoLoops(Stack<GridLocation>& path) {
    Set<GridLocation> validSet;
    Stack<GridLocation> validPath;
    while(!path.isEmpty()) {
        GridLocation location = path.pop();
        if (validSet.contains(location)) {
            validSet.add(location);
            validPath.push(location);
         }
    }
    return validPath;
}

// Helper 2
bool isCorridor(Grid<bool>& g, GridLocation location) {
    if (g[location]) {
        return true;
    }
    return false;
}

// Helper 3
bool isWithinBounds(Grid<bool>& g, GridLocation location) {
    int xBound = g.numRows()-1;
    int yBound = g.numCols()-1;
    if (location.row > xBound || location.col > yBound) {
        return false;
    } else if (location.row < 0 || location.col < 0) {
        return false;
    }
    return true;
}

// This function returns a Stack object that represents the
// path that solves the given Grid representing the maze
Stack<GridLocation> solveMaze(Grid<bool>& maze)
{
    MazeGraphics::drawGrid(maze);
    Stack<GridLocation> p;
    // TODO: your code here
    // 1. Create a queue of paths. A path is a stack of grid locations.
    Queue<Stack<GridLocation>> container;

    // 2. Create a length-one path containing just the entry location. Enqueue that path.
    Stack<GridLocation> path = {{0, 0}};
    container.enqueue(path);

    // 3. Dequeue path from queue.
    Stack<GridLocation> pathDeq = container.peek();

    while(!container.isEmpty()) {
        // 4. If this path ends at exit, this path is the solution!

        using namespace std::this_thread; // sleep_for, sleep_until
        using namespace std::chrono; // nanoseconds, system_clock, seconds
        sleep_for(milliseconds(0));
        MazeGraphics::highlightPath(pathDeq, "red");

        GridLocation exit = {maze.numRows()-1,  maze.numCols()-1};
        if (pathDeq.peek() == exit) {
            return pathDeq;
        } else {
            //container.enqueue(pathDeq);
        // 5. a. For each viable neighbor of path end, make copy of path, extend by adding neighbor and enqueue it.
        //    b. A location has up to four neighbors, one in each of the four cardinal directions. A neighbor location
        //       is viable if it is within the maze bounds, the cell is an open corridor (not a wall), and it has not
        //       yet been visit

        // 5.1 Get candidates
            Stack<GridLocation> candidates;
            GridLocation current = pathDeq.peek();
            int xCurrent = current.row;
            int yCurrent = current.col;
            // Candidates
            GridLocation up = {xCurrent-1, yCurrent};
            candidates.push(up);
            GridLocation right = {xCurrent, yCurrent+1};
            candidates.push(right);
            GridLocation down = {xCurrent+1, yCurrent};
            candidates.push(down);
            GridLocation left = {xCurrent, yCurrent-1};
            candidates.push(left);
        // 5.2 Check bounds
            Stack<GridLocation> newCandidates;
            while(!candidates.isEmpty()) {
                GridLocation location = candidates.pop();
                if (isWithinBounds(maze, location)) {
                    newCandidates.push(location);
                }
            }
        // 5.3 Check open corridor
            Stack<GridLocation> corridorCandidates;
            while(!newCandidates.isEmpty()) {
                GridLocation location = newCandidates.pop();
                if (isCorridor(maze, location)) {
                    corridorCandidates.push(location);
                }
            }
        // 5.4 Check not loop

            Stack<GridLocation> tmp = pathDeq;
            Set<GridLocation> set;
            while(!tmp.isEmpty()) {
                set.add(tmp.pop());
            }
            //for each candidate
            Stack<GridLocation> succes;
            while(!corridorCandidates.isEmpty()) {
                GridLocation location = corridorCandidates.pop();
                if (!set.contains(location)) {
                    succes.push(location);
                }
             }

        // 5.5 Enqueue it if viable
            container.dequeue(); // old
            while(!succes.isEmpty()) {
                GridLocation newStep = succes.pop();
                Stack<GridLocation> stack = pathDeq;
                stack.push(newStep);
                container.enqueue(stack);
            }
            pathDeq = container.peek(); //added
        }
    }
    return p;
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

PROVIDED_TEST("solveMaze on file 33x41") {
    Grid<bool> g;
    readMazeFile("res/33x41.maze", g);
    Stack<GridLocation> soln = solveMaze(g);

    EXPECT(checkSolution(g,soln));
}

/* * * * * * Student Test Cases For checkSolution* * * * * */
STUDENT_TEST("is WithinBounds at corner location") {
    Grid<bool> g = {{true, false}, {true, true}};
    GridLocation up = {-1, 0};
    GridLocation right = {0, 1};
    GridLocation down = {1, 0};
    GridLocation left = {0, -1};

    EXPECT_EQUAL(false, isWithinBounds(g, up));
    EXPECT_EQUAL(true, isWithinBounds(g, right));
    EXPECT_EQUAL(true, isWithinBounds(g, down));
    EXPECT_EQUAL(false, isWithinBounds(g, left));
}

STUDENT_TEST("is WithinBounds at center location") {
    Grid<bool> g = {{true, false, true}, {true, true, false}, {false, true, true}};
    int x = 1;
    int y = 1;
    GridLocation up = {x-1, y+0};
    GridLocation right = {x+0, y+1};
    GridLocation down = {x+1, y+0};
    GridLocation left = {x+0, y-1};

    EXPECT_EQUAL(true, isWithinBounds(g, up));
    EXPECT_EQUAL(true, isWithinBounds(g, right));
    EXPECT_EQUAL(true, isWithinBounds(g, down));
    EXPECT_EQUAL(true, isWithinBounds(g, left));
}

STUDENT_TEST("is the location a Corridor") {
    Grid<bool> g = {{true, false, true}, {true, true, false}, {false, true, true}};
    GridLocation loc1 {0,0};
    GridLocation loc2 {2,0};
    GridLocation loc3 {2,2};
    GridLocation loc4 {1,0};
    GridLocation loc5 {0,1};
    EXPECT_EQUAL(true, isCorridor(g, loc1));
    EXPECT_EQUAL(false, isCorridor(g, loc2));
    EXPECT_EQUAL(true, isCorridor(g, loc3));
    EXPECT_EQUAL(true, isCorridor(g, loc4));
    EXPECT_EQUAL(false, isCorridor(g, loc5));
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



