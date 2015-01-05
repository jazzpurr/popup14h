// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se
//
// https://kth.kattis.com/problems/longincsubseq

#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

void longest_increasing_subsequence(const vector<int> & X, vector<int> & LIS);

// Solves the union-find problem
int main() {
  int n; // Sequence length
  vector<int> X, LIS; // Original sequence and its LIS

  while (scanf("%i", &n) != EOF) {
    X.resize(n); // Pre-allocation
    LIS.clear();
    for (int i = 0; i < n; i++)
      scanf("%i", &X[i]); // Read all elements of the sequence
    longest_increasing_subsequence(X, LIS); // Compute LIS
    printf("%lu\n", LIS.size()); // Print LIS size
    for (auto &i : LIS)
      printf("%i ", i); // Print elements of LIS
    printf("\n");
  }
}

// Compute one longest increasing subsequence in X and populate the LIS
// vector (should be empty) with the sequence, given as the positions in X.
// Complexity: O(n log n), where n = |X|
//
// Source references:
// http://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming
// http://en.wikipedia.org/wiki/Longest_increasing_subsequence
void longest_increasing_subsequence(const vector<int> & X, vector<int> & LIS) {
  int n = X.size();

  // A[i] is the smallest number that ends an inc. subseq. of length i,
  // assisting the binary search.
  vector<int> A(n + 1, numeric_limits<int>::max());
  vector<int> S(n + 1, -1); // …while S[i] stores its index, X[S[i]] = A[i]
  vector<int> P(n); // Parent (predecessor), where P[i] is predecessor of X[i]

  int len = 0; // Length of LIS
  for (int i = 0; i < n; i++) {

    // Binary search for X[i] in A, which is already sorted
    auto it = lower_bound(A.begin(), A.end(), X[i]); // e.g. 3 => [0 1 (4) 4 5]
    int pos = it - A.begin(); // Position of it, e.g. 2
    A[pos] = X[i];
    S[pos] = i;
    P[i] = pos > 0 ? S[pos-1] : -1; // If pos = 0, it's root, thus

    if (X[i] > A[len]) // New longest LIS
      len++;
  }

  // Follow parent chain and populate LIS in reverse order
  for (int i = S[len]; i >= 0; i = P[i])
    LIS.push_back(i);
  reverse(LIS.begin(), LIS.end());
}
