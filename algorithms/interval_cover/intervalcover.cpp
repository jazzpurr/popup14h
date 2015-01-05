// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se
//
// https://kth.kattis.com/problems/intervalcover

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// An interval between a and b; or [a, b]
struct interval {
  double a, b;
  int pos; // Original position in vector (before sorting)
};

// Function that sorts interval, we will sort on a-param
bool sort_on_a(interval iv1, interval iv2) {
  return iv1.a < iv2.a;
}

void print_solution(const vector<int>& indices);
void interval_cover(double A, double B, vector<interval> intervals, vector<int>& indices);

// Solves the interval coverage problem for any number of test cases.
// Each test case starts with the interval [A, B], then a number n, followed
// by n subintervals.
int main() {
  // IO performance enhancements
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  double A, B; // Interval to cover
  int n; // Number of subintervals

  // While there is a new test case
  while (cin >> A >> B >> n) {

    vector<interval> intervals; // Subintervals
    for (int i = 0; i < n; i++) { // Read n of them
      interval iv;
      iv.pos = i;
      cin >> iv.a >> iv.b;
      intervals.push_back(iv); // Put them here
    }

    vector<int> indices;
    interval_cover(A, B, intervals, indices); // Solve, get indices
    print_solution(indices);
  }
}

// Outputs cardinality of the the subintervals and their indices,
// or "impossible" if unsolvable.
void print_solution(const vector<int>& indices) {
  if (indices.empty()) // No solution
    cout << "impossible" << endl;
  else {
    cout << indices.size() << endl; // Print cardinality followed by indices
    for (auto it = indices.cbegin(); it != indices.cend(); it++) {
      cout << *it << " ";
    }
    cout << endl;
  }
}

// Find minimum cardinality of a set of subintervals, which union includes the
// given interval [A, B]. Complexity: O(n log n), greedy approach.
//
// A, B: Interval to cover inclusive of both endpoints,
// A ≤ B, if A = B then one subinterval is needed to cover it
// intervals: Vector of subintervals
//
// Return: Vector of indices in the interval vector used to compose the
// minimum cardinality or an empty vector if subintervals cannot cover [A, B]
void interval_cover(double A, double B, vector<interval> intervals, vector<int>& indices) {

  // Sort on a-values, O(n log n)
  sort(intervals.begin(), intervals.end(), sort_on_a);

  double covered = A; // How much we have already covered from left
  auto it = intervals.begin(); // Will go exactly once from left to right

  do { // Do-while because at least one interval is always needed
    double b_max = covered; // Furthest ending of a legal subinterval
    int b_max_idx = -1;

    // For all a-values left of or equal to covered; legal subintervals
    for (; it != intervals.end() && it->a <= covered; it++) {
      if (it->b >= b_max) { // New b_max
        b_max = it->b;
        b_max_idx = it->pos;
      }
    }

    if (b_max_idx == -1) { // No legal subintervals means no solution
      indices.clear();
      break;
    }

    // Use subinterval by saving the index of it and marking it as covered
    indices.push_back(b_max_idx);
    covered = b_max;

  } while (covered < B);
}
