/*
 * File: hanoiTower.cpp
 * --------------------
 *  This program solves the Tower of Hanoi challenge
 */

#include <iostream>
#include <string>
using namespace std;

/* Prototypes */
void MoveSingleDisk(char start, char finish);
void MoveTower(int n, char start, char finish, char temp);

/* Main program */
int main() {
	cout << "Tower of Hanoi:" << endl;
	MoveTower(8, 'A', 'B', 'C');
}

/*
 * Function: MoveSingleDisk
 * Usage MoveSingleDisk('A','B');
 * ------------------------------
 *  This function moves a single disk from pile A to pile B
 */
void MoveSingleDisk(char start, char finish) {
  cout << "Move disk from: " << start << " to " << finish << endl;
}

/*
 * Function: MoveTower
 * Usage: MoveTower(8, 'A', 'B', 'C');
 * -----------------------------------
 *  This function follows the algorithm:
 *  	if (n ==1) {
 *  		// Move single disk from A to B
 *  	} else {
 *  		// Move tower from A to C
 *			// Move single disk from A to B
 *			// Move tower from C to B
 *		}
 */
void MoveTower(int n, char start, char finish, char temp) {
  if (n == 1) {
    MoveSingleDisk(start, finish);
  } else {
    // Move tower from A to C
    MoveTower(n-1, start, temp, finish);
    // Move single from A to B
    MoveSingleDisk(start, finish);
    // Move tower from C to B
    MoveTower(n-1, temp, finish, start);
  }
}
