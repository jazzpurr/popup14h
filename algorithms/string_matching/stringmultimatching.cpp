// Authors:
//  * Didrik Nordström, didrikn@kth.se
//  * Jesper Norberg, jenor@kth.se
// https://kth.kattis.com/problems/stringmultimatching

#include <iostream>
#include <vector>

#include "ahocorasick.hpp"

using namespace std;

int main() {
  // IO performance enhancements
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N; // # patterns

  while (cin >> N) {
    cin.get(); // force new line
    aho_corasick ac;

    // read patterns
    vector<string> patterns(N);
    for (int i = 0; i < N; i++) {
      getline(cin, patterns[i]);
      ac.enter(patterns[i]); // add to Aho-Corasick
    }

    // read text
    string text;
    getline(cin, text);

    // prepare the automaton and the searching
    ac.prepare();
    string_matcher m(ac, text);
    vector<vector<int>> pattern_matches(N); // keep track for output

    // perform the search
    pair<int, vector<int>> match;
    do {
      match = m.next();
      for (auto idx : match.second) // add to correct position
        pattern_matches[idx].push_back(match.first);
    } while (match.first != m.npos);

    // print all positions of each pattern found on a separate line
    for (int i = 0; i < N; i++) {
      for (auto pos : pattern_matches[i])
        cout << pos - patterns[i].length() + 1 << " "; // compensate for length
      cout << endl;
    }
  }
}
