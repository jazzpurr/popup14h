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

int N, M, sum;

void dfs(vector<bool> &visited, vector<int> &money, vector<vector<int>> &adjacencyList, int curr){
    visited[curr] = true;
	sum += money[curr];
	for (auto it = adjacencyList[curr].begin(); it != adjacencyList[curr].end(); ++it){
		if (!visited[*it]){
			dfs(visited, money, adjacencyList, *it);
		}
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	scanf("%d %d\n", &N, &M);

	bool possible = true;
	vector<bool> visited(N, false);
	vector<int> money(N);
	vector<vector<int>> adjacencyList(N);
	int a, b;

	for (int i = 0; i < N; ++i){
		scanf("%d", &money[i]);
	}
	for (int i = 0; i < M; ++i){
		scanf("%d %d\n", &a, &b);
		adjacencyList[a].push_back(b);
		adjacencyList[b].push_back(a);
	}
	for (int i = 0; i < N; ++i){
		if (!visited[i]){
			sum = 0;
			dfs(visited, money, adjacencyList, i);
			if (sum != 0){
				possible = false;
				break;
			}
		}
	}

	if (possible){
		printf("POSSIBLE");
	}
	else{
		printf("IMPOSSIBLE");
	}

	return 0;
}