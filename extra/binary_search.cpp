#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
http://www.infocobuild.com/education/audio-video-courses/computer-science/CS106B-PAbstractions-Stanford/lecture-08.html
*/

int powerRecursive(int base, int power) {
  if (power == 0) {
    return 1;
  } else {
    return base * powerRecursive(base, power-1);
  }
}

bool isPalindrome(string word) {
  if (word.length() == 1 || word.length() == 0) {
    return true;
  }
  /* Zelinski method */
  return word[0] == word[word.length()-1] && 
    isPalindrome(word.substr(1, word.length()-2));
  /*
  	My method:
		-----
  	if (word[0] == word[word.length()-1]) {
    	return isPalindrome(word.substr(1, word.length()-2));
  	} else {
    	return false;
  	}
	*/
}

int binarySearch(vector<int> v, int low, int high, int search) {
  //int low = 0;
  //int high = v.size();
  int guess = (low+high)/2;
  cout << "low: " << low << endl;
  cout << "high: " << high << endl;
  cout << "mid: " << guess << endl;
	cout << "-------------------------" << endl;

  if ( low > high) {
    return -1; //Not found
  }
  
  if (search == v.at(guess)) {
    return guess; /* base case */
  } else if (search < v.at(guess)) {
      //recursive decomposition
      cout << "search < guess" << endl;
      high = guess-1;
      return binarySearch(v, low, high, search);
  } else {
      // search > guess
      cout << "search > guess" << endl;
      low = guess+1;
      return binarySearch(v, low, high, search);
  }
}

int main() {
  string x = "Rocket ready to launch: BINARY SEARCH recursive";
  cout << x << endl;
  cout << "----------------------" << endl;
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 10, 100};
  cout << binarySearch(v, 0, v.size()-1, 8) << endl;
	return 0; 
}
