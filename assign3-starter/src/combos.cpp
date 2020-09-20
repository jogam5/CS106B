// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>     // for cout, endl
#include <string>       // for string class
#include "error.h"
#include "set.h"
#include "warmup.h"     // for factorial
#include "combos.h"
#include "testing/SimpleTest.h"
using namespace std;


// Returns the number of ways to choose k things from a set of size N
// using the formula based on factorial. Because an int type can only hold
// value of factorial up to n = 12, this formula only works correctly for
// small values of n and k.
int combo_formula(int n, int k)
{
    return factorial(n)/(factorial(k)*factorial(n-k));
}

// Returns the number of ways to choose k different elements from a set
// of size n by using a recursive formula.
int count_combos(int n, int k)
{
    if (k == 0) {
        return 1;
    }
    if (k == n) {
        return 1;
    }
    if (n < 0) {
        error("The number of n must be positive.");
    }
    if (k < 0) {
        error("The number of k must be positive.");
    }
    if (n < k) {
        error("n must be greater or equal to k");
    }
    return count_combos(n-1, k-1) + count_combos(n-1, k);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Compare count_combos to combo_formula") {
    for (int i = 0; i < 25; i++) {
        int n = randomInteger(1, 12);
        //cout << "n: " << n << endl;
        int k = randomInteger(1, n);
        //cout << "k: " << k << endl;
        EXPECT_EQUAL(count_combos(n, k), combo_formula(n, k));
    }
}

STUDENT_TEST("Combinations of n greaterthan 12") {
        EXPECT_EQUAL(455, count_combos(15,3));
}

STUDENT_TEST("Check for different errors") {
    EXPECT_ERROR(count_combos(3, 10));
    EXPECT_ERROR(count_combos(7, -3));
    EXPECT_ERROR(count_combos(-7, 1));
}

