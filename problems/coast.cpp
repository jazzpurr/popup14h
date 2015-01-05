#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

template<class T> void print(T const &x) { ostringstream os; os << x; cout << os.str() << endl; }
template<class T> void print(vector<T> const &v) { ostringstream os; for (int i = 0; i < v.size(); ++i){ if (i)os << ' '; os << v[i]; } cout << os.str() << endl; }
template<class T> void print(vector<vector<T> > const &v){ ostringstream os; for (int i = 0; i < v.size(); ++i) { for (int j = 0; j < v[i].size(); ++j){ if (j)os << ' '; os << v[i][j]; }os << endl; }cout << os.str() << endl; }
template<class T, class U> T cast(U x) { ostringstream os; os << x; T res; istringstream is(os.str()); is >> res; return res; }
template<class T> vector<T> split(string s, string x = " ") { vector<T> res; for (int i = 0; i < s.size(); i++){ string a; while (i < (int)s.size() && x.find(s[i]) == string::npos)a += s[i++]; if (!a.empty())res.push_back(cast<T>(a)); } return res; }

int nuoRows, nuoCols, counter;

void solver(vector<vector<bool>> &islandMatrix, vector<vector<bool>> &floodedMatrix, int i, int j){
    if (islandMatrix[i][j]){
		++counter;
	}

	else if (!floodedMatrix[i][j]) {
		floodedMatrix[i][j] = true;

		if (i < nuoRows - 1){
			solver(islandMatrix, floodedMatrix, i + 1, j);
		}
		if (j < nuoCols - 1){
			solver(islandMatrix, floodedMatrix, i, j + 1);
		}
		if (i > 0){
			solver(islandMatrix, floodedMatrix, i - 1, j);
		}
		if (j > 0){
			solver(islandMatrix, floodedMatrix, i, j - 1);
		}
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> nuoRows >> nuoCols;
	nuoRows += 2; //empty rows on sides
	nuoCols += 2;

	vector<vector<bool>> islandMatrix(nuoRows, vector<bool>(nuoCols, false));
	vector<vector<bool>> floodedMatrix(nuoRows, vector<bool>(nuoCols, false));

	for (int i = 1; i < nuoRows - 1; ++i) {
		for (int j = 1; j < nuoCols - 1; ++j){
			char c;
			cin >> c;
			if (c == '1'){
				islandMatrix[i][j] = true;
			}
		}
	}


	counter = 0;
	solver(islandMatrix, floodedMatrix, 0, 0);

	//print(islandMatrix);

	printf("%i\n", counter);

	return 0;
}