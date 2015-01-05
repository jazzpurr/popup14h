#include <string>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include "ahocorasick.hpp"

using std::vector;
using std::array;
using std::queue;
using std::string;
using std::move;
using std::replace;
using std::pair;
using std::make_pair;

/* Private methods */

int aho_corasick::append_state() {
  array<int, N_TRANSITIONS> transition;
  transition.fill(fail);
  g.push_back(move(transition));
  output.push_back(vector<int> ());
  f.push_back(0);
  return n_states++;
}

void aho_corasick::construct_failure() {
  queue<int> q;
  // Add all nodes from root that points to something else
  for (auto s : g[0]) {
    if (s > 0)
      q.push(s);
  }
  while (!q.empty()) {
    int r = q.front();
    q.pop();
    for (int a = 0; a < N_TRANSITIONS; a++) {
      int s = g[r][a];
      if (s == fail)
        continue;
      q.push(s);
      int state = f[r];
      while (g[state][a] == fail)
        state = f[state];

      f[s] = g[state][a];
      output[s].insert(output[s].end(), output[f[s]].begin(), output[f[s]].end());

    }
  }
}

/* Public methods */

aho_corasick::aho_corasick()
: n_states(0)
, prepared(false)
, n_patterns(0) {
  append_state();
}

void aho_corasick::enter(const string &pattern) {
  if (prepared)
    throw "Cannot enter new patterns for prepared object";

  int s = 0; // state
  int j = 0; // position in pattern
  // traverse current trie until until we need to create new subtree
  while (g[s][pattern[j]] != fail) { // while there is a next state
    s = g[s][pattern[j]]; // go to next state and increment j
    j++;
  }

  for (int p = j; p < pattern.length(); ++p) {
    int new_s = append_state();
    g[s][pattern[p]] = new_s;
    s = new_s;
  }

  output[s].push_back(n_patterns++);
}

void aho_corasick::prepare() {
  if (prepared)
    throw "Matcher already prepared";

  // Set all nodes that fail from root node 0 to itself
  replace(g[0].begin(), g[0].end(), fail, 0);

  construct_failure();
  prepared = true;
}

/* String matcher */

string_matcher::string_matcher(const aho_corasick &_ac, const string &_text)
: ac(_ac)
, text(_text)
, state(0)
, i(0) {
  if (!ac.prepared)
    throw "Cannot search if not prepared";
}

pair<int, vector<int>> string_matcher::next() {
  for (; i < text.length(); i++) {
    char a = text[i];
    while (ac.g[state][a] == ac.fail) // follow fail back edges
      state = ac.f[state];
    state = ac.g[state][a]; // until normal edge found for a
    if (!ac.output[state].empty()) // is there output here?
      return make_pair(i++, ac.output[state]); // emit result and increment
  }
  return make_pair(npos, vector<int>()); // finished
}
