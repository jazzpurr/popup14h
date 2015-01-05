#include "general.h"

struct point {
	unsigned int x, y;
	point(int _x, int _y) : x(_x), y(_y) {}
	bool operator==(const point &p) {
		return p.x == x && p.y == y;
	}
	bool operator!=(const point &p) {
		return !(*this == p);
	}
};

struct numPoint : public point {
	int n; 
	numPoint(int _x, int _y, int _n) : point(_x, _y), n(_n) {}
};

struct pattern {
	char ul, ur, dl, dr;
	pattern(string s) : ul(s[0]), ur(s[1]), dl(s[2]), dr(s[3]) {}
};

class gok {
private:
	const static vector<vector<pattern>> pattPerms; //index = n
	bool getCycles2(const point &origin);
	bool getCycles1(const point &p);
	bool cpInRange(const point &p) const;
	bool gridInRange(const point &p) const;
	vector<point> neighboursFromPoint(const point &p) const;
	pattern getPattern(const point &p) const;
	bool insertPattern(const pattern &pat, const point &p, bool force);

	const unsigned int N;
	const vector<numPoint> &nums;	
	vector<string> answer;

	bool solver2(vector<numPoint> & remaining);
	void assignStandalones();

public:
	gok(int _N, const vector<numPoint> &_nums); 
	vector<string> solver1();
};

const vector<vector<pattern>> gok::pattPerms = {
		{ pattern("/\\\\/") }, // n=0 
		{ pattern("//\\/"), pattern("/\\\\\\"), pattern("/\\//"), pattern("\\\\\\/") }, // n=1 outgoing edge
		{ pattern("//\\\\"), pattern("////"), pattern("\\/\\/"), pattern("/\\/\\"), pattern("\\\\\\\\"), pattern("\\\\//") }, // n=2 
		{ pattern("///\\"), pattern("\\/\\\\"), pattern("\\\\/\\"), pattern("\\///") }, // n=3 
		{ pattern("\\//\\") } // n=4 
};

gok::gok(int _N, const vector<numPoint> &_nums)
	: N(_N), nums(_nums) {}

bool gok::cpInRange(const point &p) const {
	return p.x <= N && p.y <= N;
}

bool gok::gridInRange(const point &p) const {
	return p.x < N && p.y < N;
}

pattern gok::getPattern(const point &p) const {
	pattern ret("xxxx");
	point ul(p.x - 1, p.y - 1);
	point ur(p.x, p.y - 1);
	point dl(p.x - 1, p.y);
	point dr(p.x, p.y);
	if (gridInRange(ul))
		ret.ul = answer[ul.y][ul.x];
	if (gridInRange(ur))
		ret.ur = answer[ur.y][ur.x];
	if (gridInRange(dl))
		ret.dl = answer[dl.y][dl.x];
	if (gridInRange(dr))
		ret.dr = answer[dr.y][dr.x];
	return ret;
}

// inserts 4-pattern to board given valid corner number. fails if inconsistent with current solution
bool gok::insertPattern(const pattern &pat, const point &p, bool force = false) {
	point ul(p.x - 1, p.y - 1);
	point ur(p.x, p.y - 1);
	point dl(p.x - 1, p.y);
	point dr(p.x, p.y);
	if (gridInRange(ul)) {
		char &c = answer[ul.y][ul.x];
		if (c == '_' || c == pat.ul || force) c = pat.ul;
		else return false;
	}
	if (gridInRange(ur)) {
		char &c = answer[ur.y][ur.x];
		if (c == '_' || c == pat.ur || force) c = pat.ur;
		else return false;
	}
	if (gridInRange(dl)) {
		char &c = answer[dl.y][dl.x];
		if (c == '_' || c == pat.dl || force) c = pat.dl;
		else return false;
	}
	if (gridInRange(dr)) {
		char &c = answer[dr.y][dr.x];
		if (c == '_' || c == pat.dr || force) c = pat.dr;
		else return false;
	}
	return true;
}

vector<point> gok::neighboursFromPoint(const point &p) const {
	vector<point> neighbors; 
	point ul(p.x - 1, p.y - 1);
	point ur(p.x, p.y - 1);
	point dl(p.x - 1, p.y);
	point dr(p.x, p.y);
	if (gridInRange(ul) && answer[ul.y][ul.x] == '\\')
		neighbors.push_back(point(p.x - 1, p.y - 1));
	if (gridInRange(ur) && answer[ur.y][ur.x] == '/')
		neighbors.push_back(point(p.x + 1, p.y - 1));
	if (gridInRange(dl) && answer[dl.y][dl.x] == '/')
		neighbors.push_back(point(p.x - 1, p.y + 1));
	if (gridInRange(dr) && answer[dr.y][dr.x] == '\\')
		neighbors.push_back(point(p.x + 1, p.y + 1));
	return neighbors;
}

bool gok::getCycles1(const point &p) {
	point north(p.x, p.y + 1);
	point south(p.x, p.y - 1);
	point west(p.x - 1, p.y);
	point east(p.x + 1, p.y);
	return (getCycles2(p) || getCycles2(north) || getCycles2(south) || getCycles2(west) || getCycles2(east));
}

bool gok::getCycles2(const point &origin) {
	if (!cpInRange(origin))
		return false;
	vvb visited(N + 1, vb(N + 1, false));
	stack<pair<point, point>> s; // Last && current
	s.push(make_pair(origin, origin));
	while (!s.empty()) {
		point curr = s.top().second; point last = s.top().first; s.pop();
		if (visited[curr.y][curr.x])
			return true;
		visited[curr.y][curr.x] = true;
		vector<point> neighbors = neighboursFromPoint(curr);
		for (auto &n : neighbors) {
			if (n != last)
				s.push(make_pair(curr, n));
		}
	}
	return false;
}

vector<string> gok::solver1() {
	answer = vector<string>(N, string(N, '_'));
	vector<numPoint> remaining(nums.begin(), nums.end());
	solver2(remaining);
	assignStandalones();
	return answer;
}

// DFS
bool gok::solver2(vector<numPoint> & remaining) {
	if (remaining.empty())
		return true;
	numPoint np = remaining.back();

	remaining.pop_back();
	pattern prev = getPattern(np); 
	for (const pattern & pattern : gok::pattPerms[np.n]) {
		insertPattern(prev, np, true);
		bool pat_ok = insertPattern(pattern, np);
		if (!pat_ok)
			continue;
		if (neighboursFromPoint(np).size() != np.n)
			continue;
		if (getCycles1(np))
			continue;
		if (solver2(remaining)) {
			return true;
		}
	}
	insertPattern(prev, np, true); // reverse
	remaining.push_back(np); 
	return false;
}

//assign standalone edges
void gok::assignStandalones() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			char &c = answer[y][x];
			if (c != '_')
				continue;
			c = '\\';
			if (getCycles2(point(x, y)))
				c = '/';
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N; // dimensions
	cin >> N;

	vector<numPoint> nums;

	for (int y = 0; y < N + 1; y++) {
		string row;
		cin >> row;
		for (int x = 0; x < N + 1; x++) {
			char c = row[x];
			if (c == '.') continue;
			int n = c - '0';
			nums.push_back(numPoint(x, y, n));
		}
	}

	gok g(N, nums);
	vector<string> answer = g.solver1();
	for (auto row : answer)
		cout << row << endl;
}
