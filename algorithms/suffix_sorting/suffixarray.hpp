
#include <string>
#include <vector>

using namespace std;

// O(n log^2 n)
// source: TopCoder forums

class suffix_array {
private:
  vector<int> suffixes;
  vector<int> ranks;
  vector<int> lcp;
  const string &str;
  const int L;
  void compute_suffix_array();
  void compute_lcp_array();

public:
  suffix_array(string _str); // constructor
  int get(int i) const; // start position of suffix #i
  int longest_common_prefix(int i) const; // lcp with aspect to previous suffix

  /**
   * Find pattern in suffix array, i.e. the suffixes with common prefix
   * to the pattern. Returns all positions in original substring.
   */
  vector<int> match(const string& pattern) const;
};
