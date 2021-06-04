/*
 * Exercise 1, Win some, lose sum.
 *

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "vector.h"
using namespace std;


/*
 * sumHelper reads in a vector and recursively compares 'target'
 * versus 'sum'. The core of the function lies in the backtracking
 * portion where we explore two possible branches following the
 * framework:
 *  Choose
 *  Recur
 *  Unchoose
 */
bool sumHelper(Vector<int>& values, int target, int sum) {
    if (values.isEmpty()) {
        /* Base case
         * Notes:
         * 1. "target == sum" is equivalent to first checking if
         * the comparision is true and later returning bool value.
         */
        return target == sum;
    } else {
        /* Recursive case
         * Notes:
         * 1. In the short circuit evaluation "||", if the first call
         * to sumHelper is true, there's no need to check for the
         * second call.
         */
        int firstElement = values[0];
        values.remove(0); // Remove the first element or 'Choose'
        bool answer = sumHelper(values, target, sum + firstElement) || sumHelper(values, target, sum); // Recur or Explore
        values.insert(0, firstElement); // Insert back the first element or Unchoose
        return answer;
    }
    return false;
}


/*
 * Win some, lose sum (Code Writing)
 * --------------------------------------------------------
 * Write a recursive function named canMakeSum that takes a
 * reference to a Vector<int> and an int target value and
 * returns true if it is possible to have some selection of
 * values from the Vector that sum to the target value.
 */
bool canMakeSum(Vector<int>& values, int target) {
    return sumHelper(values, target, 0);
}



/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Positive example from handout.") {
    Vector<int> nums = {1,1,2,3,5};
    EXPECT(canMakeSum(nums, 9));
}

PROVIDED_TEST("Provided Test: Negative example from handout"){
    Vector<int> nums = {1,4,5,6};
    EXPECT(!canMakeSum(nums, 8));
}


/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include <numeric>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "error.h"
#include "vector.h"
using namespace std;

/*
 * Weights and Balances (Code Writing)
 * --------------------------------------------------------
 * Write a recursive function that determines whether it is
 * possible to measure out the desired target amount with a
 * given set of weights, which is stored in the vector
 * weights.
 */

/*
 * Things to consider:
 * 1. Ask yourself what do you need to acumulate
 * 2. Backtracking structure: choose, recurse, unchoose
 */

bool isMeasurable(int target, Vector<int>& weights, int sum) {
    if (weights.isEmpty()) {
        // Base case
        return target == sum;
    } else {
        // Recursive case
        int n = weights[0]; // choose
        weights.remove(0);
        bool result = isMeasurable(target, weights, sum + n) || isMeasurable(target, weights, sum); // recurse
        weights.add(n); // unchoose
        return result;
    }

}

bool recurse(int target, Vector<int>& weights, int sum) {
    if (weights.isEmpty()) {
        // Base case
        return target == sum;
    } else {
        // Recursive case
        int n = weights[0]; // choose
        weights.remove(0);
        int acc = accumulate(weights.begin(),weights.end(),0);
        bool result = isMeasurable(n + target, weights, acc);
        weights.add(n); // unchoose
        return result;
    }
}


bool isMeasurable(int target, Vector<int>& weights){
    //return isMeasurable(target, weights, 0);
    return recurse(target, weights, 0);
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Additional Test: Simple Positive Example"){
    Vector<int> weights = {1, 3};
    EXPECT(isMeasurable(4, weights));
}

PROVIDED_TEST("Additional Test: Simple Positive Example"){
    Vector<int> weights = {1, 3, 5, 2};
    EXPECT(isMeasurable(7, weights));
}

PROVIDED_TEST("Additional Test: Simple Positive Example"){
    Vector<int> weights = {7, 3};
    EXPECT(isMeasurable(10, weights));
}

PROVIDED_TEST("Provided Test: Simple Positive Example"){
    Vector<int> weights = {1, 3};
    EXPECT(isMeasurable(2, weights));
}

PROVIDED_TEST("Additional Test: Simple Positive Example"){
    Vector<int> weights = {1, 3, 5};
    EXPECT(isMeasurable(4, weights));
}

PROVIDED_TEST("Provided Test: Simple Negative Example"){
    Vector<int> weights = {1, 3};
    EXPECT(!isMeasurable(5, weights));
}

PROVIDED_TEST("Provided Test: Complex Positive Example"){
    Vector<int> weights = {1, 3, 7};
    EXPECT(isMeasurable(6, weights));
}
