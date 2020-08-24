// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "balanced.h"
#include "testing/SimpleTest.h"

using namespace std;

bool isBalanced(string str) {
    string ops = operatorsOnly(str);
    return checkOperators(ops);
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
string operatorsOnly(string s)
{
    // TODO your code here
    return s;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
bool checkOperators(string s)
{
    // TODO your code here
    return false;
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsOnly on example from writeup")
{
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    string only = "(){([])(())}";
    EXPECT_EQUAL(operatorsOnly(example), only);
}

PROVIDED_TEST("checkOperators on example from writeup")
{
    string only = "(){([])(())}";
    EXPECT(checkOperators(only));
}

PROVIDED_TEST("isBalanced on example from writeup")
{
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on illegal examples from writeup")
{
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}
