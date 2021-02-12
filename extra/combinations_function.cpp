/* 
 * File: combinations_function.cpp
 * ----------------------
 * This program computes the combinations function C(n,k)
 * in a recursive fashion.
 */

#include <iostream>
#include <string>
using namespace std;

/* Prototypes */
int Combinations(int n, int k);


/* Main program */

int main() {
	int r = Combinations(6,2);
	cout << "Number of combinations: " << r << endl;
	return -1;
}

/*
 * Function: Combinations
 * Usage r = Combinations(n,k);
 * -----------------------------
 * This functions returns the combinations that result of selecting K items out of N of them. It is usually defined in terms of factorials, as follows:
 * 	C(n,k) = n! / (k! * (n-k)! )
 */
int Combinations(int n, int k) {
  if (n == k) return 1;
  if (k == 0) return 1;
  return Combinations(n-1, k-1) + Combinations(n-1,k);
}
