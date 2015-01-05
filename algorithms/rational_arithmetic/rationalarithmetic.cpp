// Authors:
//  * Didrik Nordström, didrikn@kth.se
//  * Jesper Norberg, jenor@kth.se
// https://kth.kattis.com/problems/rationalarithmetic

#include <iostream>

#include "rational.hpp"

using namespace std;

int main() {
  // IO performance enhancements
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N; // # test cases
  cin >> N;

  while (N--) {
    rational a1, a2;
    char op;
    cin >> a1 >> op >> a2;
    rational res;
    switch (op) {
    case '+':
      res = a1+a2;
      break;
    case '-':
      res = a1-a2;
      break;
    case '*':
      res = a1*a2;
      break;
    case '/':
      res = a1/a2;
      break;
    }
    cout << res << endl;
  }
}
