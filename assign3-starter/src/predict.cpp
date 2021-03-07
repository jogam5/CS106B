// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <string>
#include "predict.h"
#include "lexicon.h"
#include "set.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
using namespace std;

string reduceString(string s) {
    if (s.length() == 1) {
        return s;
    } else {
        return s[0] + reduceString(s.substr(1, s.length()-1));
    }
}

string removeString(string original, string key) {
    string::size_type i = original.find(key);
    if (i != string::npos) {
        original.erase(i, key.length());
    }
    return original;
}

/* This function recursively computes the sequences of the Tegic T9, an algorithm
 * used to predict text in a phone where only digits are present
 *
 * The base case kicksoff when there's no more digits left to add to the sequence. In this moment,
 * the 'sofar' string, which serves as variable to store the word is search in the Lex list.
 *
 * The recursive case insight lies in understanding that a branching mechanism must be used
 * to construct a path for each sequence. It uses a similar mechanism as a Heads and Tail sequence.
 */
void predict(string digits, Set<string>& suggestions, Lexicon& lex, string sofar)
{

    digits = removeString(digits,"0");
    digits = removeString(digits,"1");
    digits = removeString(digits,"*");
    digits = removeString(digits,"#");

    Map<int, string> keypad = {{2,"abc"}, {3,"def"}, {4,"ghi"}, {5,"jkl"},
                               {6,"mno"}, {7,"pqrs"},{8,"tuv"}, {9,"wxyz"}};

    string value;

    if (digits == "") value = "";
    else {
        string str = digits.substr(0,1);
        value = keypad[ stoi(str) ];
    }

    if (digits.length() == 0) {
        /* Base case */
        if (lex.contains(sofar)) {
            cout << sofar << endl;
            suggestions.add(sofar);
        }
    }
    else {
        /* Recursive case */
        predict( digits.substr(1), suggestions, lex, sofar+value[0]);
        predict( digits.substr(1), suggestions, lex, sofar+value[1]);
        predict( digits.substr(1), suggestions, lex, sofar+value[2]);
    }
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Predict intended words for digit sequence 6263, example from writeup") {
    string digits = "620630";
    Lexicon lex("res/EnglishWords.txt");
    Set<string> expected = {"name", "mane", "oboe"};
    Set<string> suggestions;

    predict(digits, suggestions, lex, "");
    EXPECT_EQUAL(suggestions, expected);
}


