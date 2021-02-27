/*
 * File: permutations.cpp
 * --------------------
 *  This program generates the permutations of a given string. Given "ABC",
 *  the output of the program is:
 *  ABC, ACB, BAC, BCA, CAB, CBA
 */

#include <iostream>
#include <string>
using namespace std;

/* Prototypes */
void Permutations(string word);
void RecursivePermutations(string prefix, string word);

/* Main Program */
int main() {
	Permutations("ABC");
	return -1;
}

/*
 * Function: Permutations
 * Usage: Permutations("ABC")
 * -----------------------------------
 *  This function is a wrapper for the RecursivePermutations() function.
 */
void Permutations(string word) {
	RecursivePermutations("", word);
}

/*
 * Function: RecursivePermutations
 * Usage: RecursivePermutations("", "ABC")
 * -----------------------------------
 *  This function computes the permutations of a given string by using a mix of
 *  recursion and a for loop.
 *
 *  The algorithm employs the following logic:
 *  if ( 'word' is empty ) 
 *  	print prefix
 * 	else  
 * 		loop over each element of 'word'
 * 		compute the new prefix by sliding or branching out 'word' to the left
 * 		compute the new word until it is reduced to ""
 * 		RecursivePermutations(newPrefix, newWord);
 *  
 *  The general principle to solve this problem is that in order to obtain the permutations
 *  of "ABC", a rule such as the following one is required:
 *  	A + permutations(BC)
 *  	B + permutations(AC)
 *  	C + permutations(AB)
 */
void RecursivePermutations(string prefix, string word) {
  if (word == "") {
    cout << prefix << endl;
  } else {
      for (int i = 0; i < word.length(); i++) {
        string newPrefix = prefix + word[i];
        //cout << "prefix: " << newPrefix << endl;
        string newWord = word.substr(0,i) + word.substr(i+1);
        //cout << "word: " << newWord << endl;
        RecursivePermutations(newPrefix, newWord);
      }
  }
}
