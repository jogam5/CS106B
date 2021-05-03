/*
 * File: subsets.cpp
 * --------------------
 *  This program generates a list of the subsets from a given
 *  set (i.e. the power set).
 *  ABC yields the subsets: {ABC} {AB} {AC} {A} {BC} {B} {C} {}
 */

#include <iostream>
#include <string>
using namespace std;

void listSubsets(string input, string soFar){
  if (input.empty()) {
    cout << "{" << soFar << "}" << endl;
  } else {
    char consider = input[0];
    string rest = input.substr(1);
    listSubsets(rest, soFar + consider);
    listSubsets(rest, soFar);
  }
}
