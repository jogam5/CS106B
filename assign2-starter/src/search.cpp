// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "testing/SimpleTest.h"
#include "map.h"
#include "set.h"
#include <string>
#include <iostream>
#include "filelib.h"
#include <fstream>
#include "simpio.h"
#include "strlib.h"
#include "search.h"
using namespace std;

Vector<string> readFile(string fileName) {
    ifstream in;
    if (!openFile(in, fileName))
        error("Cannot open file named " + fileName);
    Vector<string> lines;
    readEntireFile(in, lines);
    return lines;
}

Map<string, Vector<string>> orderFile(Vector<string> lines) {
    Map<string, Vector<string>> result;
    for (int i = 0; i < lines.size(); i++) {
        if (i % 2 == 0) {
            Vector<string> v = stringSplit(lines[i+1], " ");
            for (int i = 0; i < v.size(); i++) {
                if (v[i].empty()) {
                    v.remove(i);
                    i = i - 1;
                }
            }
            result[lines[i]] = v;
        }
    }
    return result;
}

Vector<string> discardNonWords(Vector<string> v) {
    Vector<string> result;
    for(string word : v) {
        for(int i=0; i < (int)word.length(); i++) {
            if(isalpha(word[i])) {
                result.add(word);
                break;
            }
        }
    }
    return result;
}

Vector<string> removePunct(Vector<string> v) {
    Vector<string> result;
    for(string word : v) {
        if (ispunct(word[0])) {
            word.erase(0, 1);
        }
        int lastChar = word.length()-1;
        if (ispunct(word[lastChar])) {
            word.erase(lastChar, 1);
        }
        result.add(word);
    }
    return result;
}

Vector<string> vToLower(Vector<string> v) {
    Vector<string> result;
    for (string s : v) {
        string str;
        str = toLowerCase(s);
        result.add(str);
    }
    return result;
}

Set<string> uniqueSet(Vector<string> v) {
    Set<string> unique;
    for(string word : v) {
        if (!unique.contains(word)) {
            unique.add(word);
        }
    }
    return unique;
}
// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Map<string, Set<string>> readDocs(string dbfile)
{
    Map<string, Set<string>> result;
    // 1. Reads file
    Vector<string> lines = readFile(dbfile);
    // 2. Create map
        // 2.1 Tokenize contents separated by spaces
    Map<string, Vector<string>> storage = orderFile(lines);
    for(string key : storage.keys()) {
        Vector<string> v;
        // 2.2 Discard any non-word tokens: wordk-like is a token that
        // contains at least one letter
        v = discardNonWords( storage[key] );
        // 2.3 Trim away leading and trailing punctuation marks from each token
        v = removePunct(v);
        // 2.4 Check all words should be stored in lowercase format
        v = vToLower(v);
        // 2.5 Create set of unique values
        result[key] = uniqueSet(v);
    }

    return result;
}

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Map<string, Set<string>> buildIndex(Map<string, Set<string>>& docs)
{
    Map<string, Set<string>> result;
    // TODO: your code here
    return result;
}

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Set<string> findQueryMatches(Map<string, Set<string>>& index, string sentence)
{
    Set<string> result;
    // TODO: your code here
    return result;
}

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
void searchEngine(string dbfile)
{
    // TODO: your code here
}

/* * * * * * Student Test Cases * * * * * */
STUDENT_TEST("readFile") {
    Vector<string> result = readFile("res/tiny.txt");
    Vector<string> sln = {"www.shoppinglist.com", "EGGS! milk, fish,      @  bread cheese",
            "www.rainbow.org", "red ~green~ orange yellow blue indigo violet", "www.dr.seuss.net",
            "One Fish Two Fish Red fish Blue fish !!!", "www.bigbadwolf.com", "I'm not trying to eat you"};
    EXPECT_EQUAL(result, sln);
}

STUDENT_TEST("first order information") {
    Vector<string> file = {"www.shoppinglist.com", "EGGS! milk, fish,      @  bread cheese",
            "www.rainbow.org", "red ~green~ orange yellow blue indigo violet"};
    Map<string, Vector<string>> result = orderFile(file);
    Map<string, Vector<string>> sln;
    sln["www.shoppinglist.com"] = {"EGGS!", "milk,", "fish,","@", "bread", "cheese"};
    sln["www.rainbow.org"] = {"red", "~green~", "orange", "yellow", "blue", "indigo", "violet"};
    EXPECT_EQUAL(result, sln);
}

STUDENT_TEST("discard any non-word tokens") {
    Vector<string> v1 = {"EGGS!", "milk,", "fish,","@", "bread", "cheese"};
    Vector<string> r1 = discardNonWords(v1);
    Vector<string> sln1 = {"EGGS!", "milk,", "fish,","bread", "cheese"};
    EXPECT_EQUAL(r1, sln1);

    Vector<string> v2 = {"1233", "m322", "fish,","@", "bread", "."};
    Vector<string> r2 = discardNonWords(v2);
    Vector<string> sln2 = {"m322", "fish,","bread"};
    EXPECT_EQUAL(r2, sln2);
}

STUDENT_TEST("check punctuation characters") {
    Vector<string> v1 = {"EGGS!", "@milk,", "#2fish,","*bread", "che!ese"};
    Vector<string> r1 = removePunct(v1);
    Vector<string> sln1 = {"EGGS", "milk", "2fish","bread", "che!ese"};
    EXPECT_EQUAL(r1, sln1);
}

STUDENT_TEST("string vector to lowercase") {
    Vector<string> v1 = {"EGGS", "mILk", "2fIsh","breaD", "Che!ese", "abcd"};
    Vector<string> r1 = vToLower(v1);
    Vector<string> sln1 = {"eggs", "milk", "2fish","bread", "che!ese", "abcd"};
    EXPECT_EQUAL(r1, sln1);
}

STUDENT_TEST("unique set in string Vector") {
    Vector<string> v1 = {"eggs", "eggs", "milk", "2fish","bread", "abcd", "che!ese", "abcd"};
    Set<string> r1 = uniqueSet(v1);
    Set<string> sln1 = {"eggs", "milk", "2fish","bread", "che!ese", "abcd"};
    EXPECT_EQUAL(r1, sln1);
}
/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("readDocs from tiny.txt, contains 4 documents") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    EXPECT_EQUAL(docs.size(), 4);
}

PROVIDED_TEST("readDocs from tiny.txt, suess has 5 unique words and includes lowercase fish") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Set<string> seuss = docs["www.dr.seuss.net"];
    EXPECT_EQUAL(seuss.size(), 5);
    EXPECT(seuss.contains("fish"));
    EXPECT(!seuss.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 20 unique tokens overall") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    EXPECT_EQUAL(index.size(), 20);
    EXPECT(index.containsKey("fish"));
    EXPECT(!index.containsKey("@"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 3);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here
