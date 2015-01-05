// Authors:
//  * Didrik Nordström, didrikn@kth.se
//  * Jesper Norberg, jenor@kth.se
// https://kth.kattis.com/problems/stringmatching

#include "ahocorasick.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  // IO performance enhancements
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string pattern, text;

  while (getline(cin, pattern)) {
    getline(cin, text);

    // create aho_corasick object and prepare for searching
    aho_corasick ac;
    ac.enter(pattern);
    ac.prepare();
    string_matcher matcher(ac, text);

    // search
    pair<int, vector<int>> match = matcher.next();
    while (match.first != matcher.npos) {
      cout << match.first - pattern.length() + 1 << " ";
      match = matcher.next();
    }
    cout << endl;
  }
}
