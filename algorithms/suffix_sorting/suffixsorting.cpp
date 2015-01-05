// Authors:
//  * Didrik Nordström, didrikn@kth.se
//  * Jesper Norberg, jenor@kth.se
// https://kth.kattis.com/problems/suffixsorting

#include "suffixarray.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // IO performance enhancements
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string line;
  int n; // #queries
  int current;

  while (true) {
    getline(cin, line);
    if (cin.fail())
      break;
    suffix_array sa(line);
    cin >> n;
    while (n--) {
      cin >> current;
      cout << sa.get(current+1) << " ";
    }
    cin.get();
    cout << endl;
  }
}
