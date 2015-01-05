
#include "suffixarray.hpp"

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// suffixes = The suffix array. Is to contain the n suffixes of input sorted
// lexicographically,  represented by starting position in string ranks =
// inverse of suffixArray, ranks[i] = index of suffixes[i...n] as such,
// suffixes[i] = k <==> ranks[k] = i. This allows comparing suffixes in O(1),
// as suffixes[i...n] < suffixes[j...n] if ranks[i]<ranks[j]

suffix_array::suffix_array(string _str)
: str(_str)
, L(str.length()) {
  ranks.resize(L+1);
  lcp.resize(L+1);
  compute_suffix_array();
  compute_lcp_array();
}

void suffix_array::compute_suffix_array() {
  int it = 1;
  for (int i = 0; i < L; i++)
    ranks[i] = str[i];
  ranks[L] = 0;
  vector<int> tmp(L+1, 0);
  suffixes.resize(L+1);
  iota(suffixes.begin(), suffixes.end(), 0);

  // Comparison function
  auto compare = [&](int i, int j) {
    if (ranks[i] == ranks[j]) {
      i += it;
      j += it;
      if (i < L && j < L)
        return ranks[i] < ranks[j];
      else
        return i > j;
    }
    return ranks[i] < ranks[j];
  };

  do {

    // use it-1 ranking (ranking of 2^(it-1)-grams) to sort 2^it-grams
    sort(suffixes.begin(), suffixes.end(), compare);

    // lexographic renaming => store the ranking of each gram in the sorted
    // bigrams (suffixes)
    for (int i = 0; i < L; i++) {
      bool higher = compare(suffixes[i], suffixes[i+1]);
      tmp[i+1] = tmp[i] + higher;
    }

    // update ranks
    for (int i = 0; i < L+1; i++)
      ranks[suffixes[i]] = tmp[i];

    it <<= 1; // checking for 2^(it+1)-grams next iteration
  } while (tmp[L] < L);
}

void suffix_array::compute_lcp_array() {
  lcp[0] = 0;
  int h = 0; // offset
  for (int i = 0; i < L; i++) {
    if (ranks[i] == 0) {
      lcp[i] = 0;
      continue;
    }
    int j = suffixes[ranks[i]-1];
    for (; i+h < L && j+h < L && str[i+h] == str[j+h]; h++);
    lcp[ranks[i]] = h;
    if (h > 0)
      h--;
  }
}

int suffix_array::get(int i) const {
  return suffixes[i];
}

int suffix_array::longest_common_prefix(int i) const {
  return lcp[i];
}

vector<int> suffix_array::match(const string& pattern) const {
  vector<int> matches;
  int lcp_len = 0;
  int matched = 0; // # matched chars
  int i;
  for (i = 1; i < L+1; i++) {
    if (lcp[i] < matched)
      return matches;
    while (suffixes[i] + matched <= L && str[suffixes[i] + matched] == pattern[matched]) {
      if (++matched == pattern.length()) {
        goto outer; // found
      }
    }
  }
  outer:
  matches.push_back(suffixes[i]);
  for (int j = i+1; j < L+1 && lcp[j] >= pattern.length(); j++) {
    matches.push_back(suffixes[j]);
  }
  sort(matches.begin(), matches.end());
  return matches;
}
