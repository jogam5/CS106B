/**
 * File: warmup.cpp
 * ----------------
 * @author Julie Zelenski, Spring 2020
 * This code is provided as part of an exercise to practice using a
 * debugger. This program has buggy use of recursion.
 */

#include <iostream>    // for cout, endl
#include "error.h"
#include "random.h"
#include "testing/SimpleTest.h"
using namespace std;


// Recurisve implementation of factorial
// Works correctly for positive values of n whose computed factorial
// does not overflow int (n <= 12)
// Does not correctly handle negative inputs
int factorial(int n)
{
    if (n < 0) {
        error("The given number must be positive.");
    }
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}


// Interactive implementation of raise base to exponent
// Works correctly for both positive and negative exponents
// Result is of type double to return real values instead of integer
double iterativePower(int base, int exp)
{
    double result = 1;

    if (base == 0) {
      return 0;
    }
    for (int i = 0; i < abs(exp); i++) {
        result *= base;
    }
    if (exp < 0) {
        result = 1/result; // reciprocal for negative exponent
    }
    return result;
}

// Recursion implementation of raise base to exponent. BUGGY!
// Mostly works correctly but has bugs to find and fix. Refer to
// writeup.
double power(int base, int exp)
{
    if (exp == 0) {
        return 1;
    } else if (exp == 0 && base == 0) {
        error("Result could be 0 or 1");
    }
    else if (exp < 0) {
        return 1/power(base, -exp);
    } else {
        return base*power(base, exp-1);
    }
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test factorial function on simple input") {
    EXPECT_EQUAL(factorial(7), 7*6*5*4*3*2);
}

STUDENT_TEST("Test for negative value") {
    EXPECT_ERROR(factorial(-7));
}

PROVIDED_TEST("Test recursive power against iterative power, random inputs") {
    for (int i = 0; i < 25; i++) {
        int base = randomInteger(1, 20);
        int exp = randomInteger(0, 10);
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test random negative base and negative exponent") {
    for (int i = 0; i < 25; i++) {
        int base = randomInteger(-10, 20);
        int exp = randomInteger(-10, 10);
        cout << base << " - " << exp << endl;
        EXPECT_EQUAL(power(base, exp), iterativePower(base, exp));
    }
}

STUDENT_TEST("Test for zero raised to the power of zero") {
    for (int i = 0; i < 25; i++) {
        int exp = randomInteger(1, 10);
        EXPECT_EQUAL(power(0, exp), 0);
    }
}


