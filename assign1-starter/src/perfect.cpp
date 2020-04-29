// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "timer.h"
#include "vector.h"
using namespace std;


// Return sum of all divisors of n, excluding self
long divisorSum(long n)
{
    long total = 0;

    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

// A smarter version of the last function
long smarterSum(long n) {
    long total = 0;

    for (long divisor = 1; divisor < sqrt(n); divisor++) {
        if (n % divisor == 0) {
            total += divisor;
            if (divisor > 1) {
                total += n / divisor; // inverse pair
            }
        }

    }
    if ( n > 1) {
        // if a number is a perfect square add to 'total' the square root of 'n'
        long double sr = sqrt(n);
        if( (sr - floor(sr)) == 0) {
            total += sqrt(n);
        }
    }
    return total;
}

/* 
To get practice with writing good comments, write a comment here
explaining the functionality of this function.
*/
bool isPerfect(long n)
{
    return (n != 0) && (n == smarterSum(n));
}

/* 
To get practice with writing good comments, write a comment here
explaining the functionality of this function.
*/
void findPerfects(int stop)
{
    Timer t;
    t.start();

    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
    }
    int secs = t.stop()/1000; // timer counts in milliseconds
    cout << "Searched up to " << addCommasTo(stop) << " in " << (secs/60) << " min and " << secs % 60 << " secs." << endl;
}


/*
To get practice with writing good comments, write a comment here
explaining the functionality of this function.
*/

bool isPrime(int n)
{
    if (n == 1) {
        return false;
    }
    for(int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

Vector<long> findByEuclid(int n)
{
    Vector<long> vec;
    int k = 1;
    while (vec.size() < n) {
        int m = pow(2,k) - 1;
        if ( isPrime(m) ) {
            vec.add( pow(2,k-1) * m );
        }
        k++;
    }
    return vec;
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Check divisorSum vs smarterSum") {
    EXPECT_EQUAL(divisorSum(6), smarterSum(6));
    EXPECT_EQUAL(divisorSum(4), smarterSum(4));
    EXPECT_EQUAL(divisorSum(25), smarterSum(25));
    EXPECT_EQUAL(divisorSum(5), smarterSum(5));
}

PROVIDED_TEST("Check divisor sums of small numbers") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Check 6 and 28, should be perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Imperfect numbers") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Oddballs, zero, one, negative") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
    EXPECT(!isPerfect(-6));
}

PROVIDED_TEST("check negative values") {
    EXPECT(!isPerfect(-5));
    EXPECT(!isPerfect(-100));
}

PROVIDED_TEST("33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("5 is perfect") {
    EXPECT(!isPerfect(5));
}

// TODO: add your test cases here

PROVIDED_TEST("Check is Prime function") {
    EXPECT(!isPrime(1));
    EXPECT(isPrime(2));
    EXPECT(isPrime(3));
    EXPECT(isPrime(7));
    EXPECT(isPrime(23));
    EXPECT(isPrime(31));
    EXPECT(isPrime(37));
}

PROVIDED_TEST("Check Euclid function") {
    Vector<long> goal = {6, 28, 496, 8128};
    EXPECT_EQUAL(goal, findByEuclid(4));
}
