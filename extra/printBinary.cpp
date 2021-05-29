/*
 * File: printBinary.cpp
 * --------------------
 *  This program uses recursive backtracking to print all 
 *  binary numbers that have exactly the number of digits
 *  given as input
 */

#include <iostream>
#include <string>
using namespace std;

/* Prototypes */
void printAllBinary(int n, string sofar);

/* Main */
int main() {
	printAllBinary(3, "");
	return -1;
}

void printAllBinary(int n, string sofar) {
	// Base case
	if (n == 0) {
		cout << sofar << endl;
	} else {
	// Recursive backtracking
		printAllBinary(n-1, sofar+"0");
		printAllBinary(n-1, sofar+"1");
	}
}
