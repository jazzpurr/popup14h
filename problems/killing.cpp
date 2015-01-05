
#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <queue>

using namespace std;

template<class T> void print(T const &x) { ostringstream os; os << x; cout << os.str() << endl; }
template<class T> void print(vector<T> const &v) { ostringstream os; for (int i = 0; i < v.size(); ++i){ if (i)os << ' '; os << v[i]; } cout << os.str() << endl; }
template<class T> void print(vector<vector<T> > const &v){ ostringstream os; for (int i = 0; i < v.size(); ++i) { for (int j = 0; j < v[i].size(); ++j){ if (j)os << ' '; os << v[i][j]; }os << endl; }cout << os.str() << endl; }
template<class T, class U> T cast(U x) { ostringstream os; os << x; T res; istringstream is(os.str()); is >> res; return res; }
template<class T> vector<T> split(string s, string x = " ") { vector<T> res; for (int i = 0; i < s.size(); i++){ string a; while (i < (int)s.size() && x.find(s[i]) == string::npos)a += s[i++]; if (!a.empty())res.push_back(cast<T>(a)); } return res; }

#define INF 0x3fffffff
#define maxSize 51 

int nuoRows, nuoCols, remainingAliens;
char maze[maxSize][maxSize];
int shortestPath[maxSize][maxSize];
int startR, startC;

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

struct Node {
	int r;
	int c;
	int w;
	Node(int i1, int i2, int i3)
		: r(i1), c(i2),	w(i3) {}
	bool operator < (const Node &n)const {
		return w>n.w;
	}
};

int bfs() {
	int res = 0;
	priority_queue<Node> pQ;
	pQ.push(Node(startR, startC, 0));
	vector<vector<int>> shortestPath(nuoRows, vector<int>(nuoCols, INF));
	shortestPath[startR][startC] = 0;

	while (!pQ.empty() || remainingAliens) {
		Node curr = pQ.top(); pQ.pop();

		if (maze[curr.r][curr.c] == 'A') {
			res += curr.w;
			curr.w = 0;
			maze[curr.r][curr.c] = ' ';
			remainingAliens--;
		}

		for (int i = 0; i < 4; i++) {
			int tr = curr.r + dx[i];
			int tc = curr.c + dy[i];
			int tw = curr.w + 1;
			if (maze[tr][tc] != '#' && shortestPath[tr][tc] > tw) {
				pQ.push(Node(tr, tc, tw));
				shortestPath[tr][tc] = tw;
			}
		}
	}

	return res;
}

int main(){

	int nuoTestCases;
	scanf("%d", &nuoTestCases);

	while (nuoTestCases--) {
		remainingAliens = 0;

		cin >> nuoCols >> nuoRows;
		int nodeID = 0;
		cin.ignore(1); //clears newline sign
		for (int i = 0; i < nuoRows; i++) {
			cin.getline(maze[i], maxSize);
			for (int j = 0; j < nuoCols; j++) {
				switch (maze[i][j]) {
				case 'S':
					startR = i;
					startC = j;
					break;
				case 'A':
					remainingAliens++;
					break;
				default:
					break;
				}
			}
		}

		printf("%d\n", bfs());
	}

	return 0;
}