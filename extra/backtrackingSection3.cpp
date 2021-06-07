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
 * 3. In the case B it's not a whole sum, it could be a partial sum. Thus
 * probably is much more similar to what we have done before. Try sketching
 * a tree.
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

// To do:
// Refactor, Join Methods, Run tree to understand || short circuit operator, Understand when Unchoose
bool isSum(int sum, int target, Vector<int> v) {
    if (v.isEmpty()) return false;
    if (sum == target + v[0]) {
        cout << "sum: " << sum << ", target: " << target << ", v[0]: " << v[0] << endl;
        return true;
     }

    else {
        v.remove(0);
        return isSum(sum, target, v);
    }
}

bool recurse(int target, Vector<int>& weights, int sum, Vector<int> original) {
    if (weights.isEmpty()) {
        // Base case
        //return target == sum;
        cout << "sum: " << sum << ", target: " << target << endl;
        return isSum(sum, target, original);
    } else {
        // Recursive case
        int n = weights[0]; // choose
        weights.remove(0);

        //int acc = accumulate(weights.begin(),weights.end(),0);
        //cout << "sum entering recurse: " << sum + n << endl;
        bool result = recurse(target, weights, sum + n, original) || recurse(target, weights, sum, original);
        //recurse(target, weights, sum + n, original);
        //recurse(target, weights, sum, original);
        weights.add(n); // unchoose
        return result;
    }
    //return false;
}


bool isMeasurable(int target, Vector<int>& weights){
    //return isMeasurable(target, weights, 0);
    Vector<int> original = weights;
    return recurse(target, weights, 0, original);
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

