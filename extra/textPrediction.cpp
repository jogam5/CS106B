/*
 * File: textPrediction.cpp
 * --------------------
 *  This program generates the sequence of a
 *  branch of numbers used in the algorithm
 *  Tegic T9.
 */

#include <iostream>
#include <string>
using namespace std;

/* Prototypes */
void Mnemonics(int n, string sofar, string digits);

/* Main Program */
int main() {
	string digits = "6263";
	Mnemonics(digits.length(), "", digits);
	return -1;
}

/*
 * Function: Mnemonics
 * Usage: Mnemonics(n, "", "6263")
 * -----------------------------------
 *  This function computes the sequence of characters
 *  used in the Tegic T9 algorithm.
 */
void Mnemonics(int n, string sofar, string digits) {
  // Reflection:
  /*
  I arrived to this solution after understanding how to create
  a recursive implementation of a program to figure out the 
  different sequences when a fair coin is flipped. That is, if
  a coin is flipped two times, the potential sequences are:
  HT, TH.

  I understood that a coin flip works in a similar way to the
  problem at hand because the flipping of a coin can be understood
  using a Decision Tree. Thus, I sketched out a decision Tree
  for my problem.

  The key insight that led me to try this approach was to think that
  a decision tree for a coin toss has two branches. In a similar vein,
  the problem at hand has three branches from where different Permutations
  are processed. In addition, I had already employed a way to map the
  expected phone number to the strings on the phone pad.

  Finally, I believe that this approach (branching) is likely to work
  in similar problems where a branch and a "sofar" string is being
  constructed. This is a recursive function that follows the template:
  "Print and Find all the solutions". At last I feel delighted that
  I was able to figure out a solution without using a loop. I was lucky
  enough to had a stroke of intuition and write the solution in a
  couple of minutes.
  */

  // Begin -> Map numbers
  string value = "";
  if ( digits[0] == '2') value = "ABC";
  if ( digits[0] == '3') value = "DEF";
  if ( digits[0] == '6') value = "MNO";
  // End -> Map Numbers
  
  if (n == 0) cout << sofar << endl;
  else {
    Mnemonics(n-1, sofar+value[0], digits.substr(1));
    Mnemonics(n-1, sofar+value[1], digits.substr(1));
    Mnemonics(n-1, sofar+value[2], digits.substr(1));
  }
}
