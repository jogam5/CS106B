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

// This function computes the midpoint between point A and point B
// using the GPoint object
GPoint midPoint(GPoint a, GPoint b) {
    GPoint point ((a.getX()+b.getX())/2, (a.getY()+b.getY())/2);
    return point;
}

/*
 * This function uses recursion to create a fractal of triangles
 * named Sierpinski Triangle.
 * Problem: figure out the right coordinates for the vertices of each triangle.
 * Lessons learned:
 * 1. The y coordinates should be computed by the midpoint, not by simple division by 2
 * 2. The base case in recursion is fundamental, I understood what I had to do but spent hours
 * trying to organize my mind around how to call the recursive functions
 * 3. Logging information is crucial for debugging
 * 4. The key insight was when I realized that I was computing the right coordinates for the points
 * but the smaller triangles were hiddent behind the biggest triangle.
 * 5. Next time I should debug faster and double check the base case
*/
void drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
   if (order == 0) {
    fillBlackTriangle(window, one, two, three);
    cout << "Draws triangle: " << one << two << three << endl;
    cout << "" << endl;
   }
   if (order > 0) {
       drawSierpinskiTriangle(window, one, midPoint(one, two), midPoint(one, three), order-1);
       drawSierpinskiTriangle(window, midPoint(one, two), two, midPoint(two, three), order-1);
       drawSierpinskiTriangle(window, midPoint(one, three), midPoint(two, three), three, order-1);
   }
}

/* * * * * * Test Cases * * * * * */

void runDemos();

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runDemos();
}
