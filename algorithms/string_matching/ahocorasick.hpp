#ifndef AHO_CORASICK_HPP
#define AHO_CORASICK_HPP

// Max number of ∂-functions from one state to another (7-bit ASCII)
#define N_TRANSITIONS (128)

#include <vector>
#include <array>
#include <string>

using std::vector;
using std::array;
using std::string;
using std::pair;

/**
  Multimatcher based on Aho-Corasick algorithm
 */
class aho_corasick {

  friend class string_matcher;

private:
  const int fail = -1; // fail transition
  bool prepared; // initially false. no more patterns can be entered after set.
  int n_states; // internal states in the automaton/trie
  int n_patterns; // input patterns
  
  // g[s][c] is the transition from state s on char c to another state s'
  vector<array<int, N_TRANSITIONS>> g;
  // output[s] is a list of id:s of the matched patterns in this state
  vector<vector<int>> output;
  vector<int> f; // failure function, applied when transition fails

  // Appends an empty state, returns it and adjusts internal vector sizes
  int append_state();

  // BFS to construct failure (back) nodes in automaton
  void construct_failure();

public:

  aho_corasick(); // simple constructor

  void enter(const string &pattern); // add pattern to search for

  // Create the automaton and prepare for search. After preparation, only
  // searching is allowed.
  void prepare();

};

/**
  A matcher, which can be polled until no more matches are found within the
  text. The order it will emit matches will not correspond to the start
  positions but rather the end positions of the patterns in the text.
 */
class string_matcher {

private:
  const aho_corasick &ac; // reference to the trie
  const string &text;
  int state; // current state in trie
  int i; // position in text string

public:
  // indicating not found in the search
  const size_t npos = -1;

  // Search on a prepared aho_corasick object
  string_matcher(const aho_corasick &_ac, const string &_text);

  // Find next match. First is position in text, second is id:s of patterns that
  // matched. If finished, it will return string_matcher::npos as position.
  pair<int, vector<int>> next();
};

#endif
