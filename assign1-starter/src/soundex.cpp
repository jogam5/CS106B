// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include <fstream>
#include <cctype>
#include "simpio.h"
#include <string>
using namespace std;

/*
This function takes a string by reference and modifies the string
to remove all non-letter characters from it. 
WARNIING: The provided code is buggy! 
Use unit tests to identify which inputs are mishandled.
Then, remove this comment and replace it with a description of the bug you fixed.
*/
void removeNonLetters(string& s)
{
    //char special = '#';
    for (int i = 0; i < (int)s.length(); i++) {
        if (!isalpha(s[i])) {
            s.erase(i, 1);
            i--;
        }
    }
}

/*
This function receives a string by reference and econdes
each letter of the string as a digit given a specific table
of values
*/

string encodeLetters(string s) {
    string result;
    string x;
    for(int i = 0; i < (int)s.length(); i++) {
        x += toupper(s[i]);
    }
    s = x;
    for (int i = 0; i < (int)x.length(); i++) {
        switch(s[i]) {
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
            case 'H':
            case 'W':
            case 'Y':
                result += '0';
                break;
            case 'B':
            case 'F':
            case 'P':
            case 'V':
                result += '1';
                break;
            case 'C':
            case 'G':
            case 'J':
            case 'K':
            case 'Q':
            case 'S':
            case 'X':
            case 'Z':
                result += '2';
                break;
            case 'D':
            case 'T':
                result += '3';
                break;
            case 'L':
                result += '4';
                break;
            case 'M':
            case 'N':
                result += '5';
                break;
            case 'R':
                result += '6';
                break;
        }
    }
    return result;
}

/*
This function receives a number given as string
and coalesces adjacent duplicates
(e.g. 222025 becomes 2025)
*/
void coalesce(string& s){
    for(int i = 0; i < (int)s.length(); i++) {
        if ( s[i] == s[i+1] ) {
            s.erase(i,1);
            i--;
        }
    }
}

/*
This function removes all zeros from the given digit
given in a string type
*/
void removeZeros(string& s) {
    for(int i = 0; i < (int)s.length(); i++) {
        if (s[i] == '0') {
            s.erase(i,1);
            i--;
        }
    }
}

/*
Write a function that makes the code's length exactly 4 digits
*/
void makeFourDigits(string& s) {
    if (s.length() > 4) {
        s.erase(4, s.length() - 2);
    }
    while( s.length() < 4 ) {
        s += "0";
    }
}

/* 
To get practice with writing good comments, write a comment here
explaining the functionality of this function.
*/
string soundex(string s)
{
    // Store the result in this variable
    string result;
    // 1. discard all non letters
    removeNonLetters(s);
    // 2. store first letter in uppercase format
    char firstChar = s[0];
    firstChar = toupper(firstChar);
    string firstLetter;
    firstLetter.append(1, firstChar);
    // 3. encode letters as digits
    result = encodeLetters(s);
    // 4. coalesce adjacent duplicates
    coalesce(result);
    // 5. replace first digit
    result.erase(0, 1);
    result.insert(0, firstLetter);
    // 6. remove zeros
    removeZeros(result);
    // 7. compress to four digits
    makeFourDigits(result);

    return result;
}

/* 
To get practice with writing good comments, write a comment here
explaining the functionality of this function.
*/
void soundexSearch(string filepath)
{
    // 1. Read the file
    // The proivded code opens the file with the given name 
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> lines;

    if (openFile(in, filepath)) {
        readEntireFile(in, lines);
    }
    cout << "Read file " << filepath << ", " << lines.size() << " names found." << endl;

    // The names in the database are now stored in the provided Vector
    // named lines
    
    // TODO: your code here!
    while (true) {
        // 2. Ask for a surname
        cout << "Enter a surname (Q to quit):" << endl;
        string surname;
        cin >> surname;

        if (surname == "Q") {
            break;
        }

        // 3. Compute the code
        string code = soundex(surname);
        // 4. Iterate over the database
        Vector<string> results;
        for(int i = 0; i < lines.size(); i++) {
          if ( soundex(lines[i]) == code ) {
              results.add(lines[i]);
          }
        }
        // 5. Print matches in sorted array
        results.sort();
        cout << results << endl;
    }
    cout << "All done" << endl;
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s;

    s = "O'Hara";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "OHara");
    s = "Planet9";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "Planet");
    s = "tl dr";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "tldr");
    s = "## abc";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "abc");
    s = "67878 #33?";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "");
    s = "";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "");
    s = "123456";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "");
    s = "1234 56";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "");
    s = " 123456";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "");
    s = " ";
    removeNonLetters(s);
    EXPECT_EQUAL(s, "");
}

PROVIDED_TEST("Encode a string") {
    string s;
    s = "GREGG";
    string r = encodeLetters(s);
    EXPECT_EQUAL(r, "26022");

    s = "ISLAS";
    r = encodeLetters(s);
    EXPECT_EQUAL(r, "02402");
}

PROVIDED_TEST("Coalesce duplicate digits") {
    string s;
    s = "222025";
    coalesce(s);
    EXPECT_EQUAL(s, "2025");

    s = "";
    coalesce(s);
    EXPECT_EQUAL(s, "");

    s = "6022";
    coalesce(s);
    EXPECT_EQUAL(s, "602");
}

PROVIDED_TEST("Remove zeros from code") {
    string s;
    s = "2025";
    removeZeros(s);
    EXPECT_EQUAL(s, "225");

    s = "A0336";
    removeZeros(s);
    EXPECT_EQUAL(s, "A336");

    s = "0000";
    removeZeros(s);
    EXPECT_EQUAL(s, "");
}

PROVIDED_TEST("Make four digits") {
    // Bug
    string s;
    s = "GRA1TY";
    makeFourDigits(s);
    EXPECT_EQUAL(s, "GRA1");

    s = "I38";
    makeFourDigits(s);
    EXPECT_EQUAL(s, "I380");

    s = "";
    makeFourDigits(s);
    EXPECT_EQUAL(s, "0000");
}

PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Zelenski"), "Z452");
    EXPECT_EQUAL(soundex("Gregg"), "G620");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here

