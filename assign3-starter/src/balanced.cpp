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

/**
 * This function receives a string and erases all its characters except
 * the operators: (), [] and {}
 */
string operatorsOnly(string s)
{
    int d = s.length();
    if ( s.empty() ) {
        return "";
    }
    if (s[d-1] == '[' || s[d-1] == ']' || s[d-1] ==  '(' || s[d-1] == ')' || s[d-1] == '{' || s[d-1] == '}' ) {
        return operatorsOnly(s.erase(d-1,1)) += s[d-1];
    } else {
        return operatorsOnly(s.erase(d-1,1));
    }
    return "";
}

/**
 * This function receives a string of operators and returns true if the
 * operators are balanced.
 */
bool checkOperators(string s)
{
    if (s.empty()) {
        return true;
    } else if (s.find("()") != string::npos) {
        size_t pos = s.find("()");
        return checkOperators(s.erase(pos,2));
    } else if (s.find("[]") != string::npos) {
        size_t pos = s.find("[]");
        return checkOperators(s.erase(pos,2));
    } else if (s.find("{}") != string::npos) {
        size_t pos = s.find("{}");
        return checkOperators(s.erase(pos,2));
    } else {
        return false;
    }
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
