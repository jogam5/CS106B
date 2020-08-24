// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "fractal.h"
#include "error.h"
#include "testing/SimpleTest.h"
using namespace std;



/**
 * Fill a triangle defined by the corner GPoints one, two, and three.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
   // TODO your code here
}

/* * * * * * Test Cases * * * * * */

void runDemos();

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runDemos();
}

