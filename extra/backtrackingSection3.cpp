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
