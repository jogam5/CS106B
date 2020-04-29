#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "perfect.h"
#include "soundex.h"
using namespace std;


int main() 
{
    if (runSimpleTests(NO_TESTS)) {
        return 0;
    }
    /*
    findPerfects(80000);
    Vector<long> vec = findByEuclid(5);
    for(int value : vec) {
        cout << value << endl;
    }

    // Comment out the above line and uncomment below line 
    // to switch between running perfect.cpp and soundex.cpp
    */
    soundexSearch("res/surnames.txt");


    return 0;
}
