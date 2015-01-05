#include "general.h"

int targetIndex(int x, int y) {
	return y * 9 + x;
}

void clockwiseRotation(vector<char> &currMap) {
	const int f = 4;
	const int n = 9;

	for (int x = 0; x < f; x++) {
		for (int y = 0; y <= f; y++) {
			char temp = currMap[targetIndex(x, y)];
			currMap[targetIndex(x, y)] = currMap[targetIndex(y, n - 1 - x)];
			currMap[targetIndex(y, n - 1 - x)] = currMap[targetIndex(n - 1 - x, n - 1 - y)];
			currMap[targetIndex(n - 1 - x, n - 1 - y)] = currMap[targetIndex(n - 1 - y, x)];
			currMap[targetIndex(n - 1 - y, x)] = temp;
		}
	}
}

void setRow(const vector<char> &fromMap, vector<char> &currMap, int row_segment, int a, int b) {
	auto r_seg = fromMap.begin() + row_segment * 27;
	auto a_begin = r_seg + a * 9;
	auto a_end = a_begin + 9;
	auto b_begin = currMap.begin() + row_segment * 27 + b * 9;
	copy(a_begin, a_end, b_begin);
}

void setRowSeg(const vector<char> &fromMap, vector<char> &currMap, int a, int b) {
	auto a_begin = fromMap.begin() + a * 27;
	auto a_end = a_begin + 27;
	auto b_begin = currMap.begin() + b * 27;
	copy(a_begin, a_end, b_begin);
}

void setCol(const vector<char> &fromMap, vector<char> &currMap, int column_segment, int a, int b) {
	int offset_a = column_segment * 3 + a;
	int offset_b = column_segment * 3 + b;
	for (int i = 0; i < 9; i++) {
		currMap[offset_b + 9 * i] = fromMap[offset_a + 9 * i];
	}
}

void setColSeg(const vector<char> &fromMap, vector<char> &currMap, int a, int b) {
	int offset_a = a * 3;
	int offset_b = b * 3;
	for (int i = 0; i < 9; i++) {
		auto a_begin = fromMap.begin() + 9 * i + offset_a;
		auto a_end = a_begin + 3;
		auto b_begin = currMap.begin() + 9 * i + offset_b;
		copy(a_begin, a_end, b_begin);
	}
}

bool checkDeriv(const vector<char> &incompleteMap, const vector<char> &completeMap, int x_min = 0, int w = 9) {
	vector<char> f(10, -1);
	for (int y = 0; y < 0 + 9; y++) {
		for (int x = x_min; x < x_min + w; x++) {
			char i = incompleteMap[targetIndex(x, y)];
			char c = completeMap[targetIndex(x, y)];
			if (i == 0)
				continue;
			if (f[i] == -1)
				f[i] = c;
			else if (f[i] != c)
				return false;
		}
	}
	return true;
}

const vector<vector<int>> perms = {
		{ 0, 1, 2 },
		{ 0, 2, 1 },
		{ 1, 0, 2 },
		{ 1, 2, 0 },
		{ 2, 0, 1 },
		{ 2, 1, 0 },
};

bool loop8(const vector<char> &incompleteMap, vector<char> completeMap) {
	if (!checkDeriv(incompleteMap, completeMap, 3, 3))
		return false;
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setCol(cache, completeMap, 2, l, perm[l]);
		if (checkDeriv(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool loop7(const vector<char> &incompleteMap, vector<char> completeMap) {
	if (!checkDeriv(incompleteMap, completeMap, 0, 3))
		return false;
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setCol(cache, completeMap, 1, l, perm[l]);
		if (loop8(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool loop6(const vector<char> &incompleteMap, vector<char> completeMap) {
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setCol(cache, completeMap, 0, l, perm[l]);
		if (loop7(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool loop5(const vector<char> &incompleteMap, vector<char> completeMap) {
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setRow(cache, completeMap, 2, l, perm[l]);
		if (loop6(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool loop4(const vector<char> &incompleteMap, vector<char> completeMap) {
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setRow(cache, completeMap, 1, l, perm[l]);
		if (loop5(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool loop3(const vector<char> &incompleteMap, vector<char> completeMap) {
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setRow(cache, completeMap, 0, l, perm[l]);
		if (loop4(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool loop2(const vector<char> &incompleteMap, vector<char> completeMap) {
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setRowSeg(cache, completeMap, l, perm[l]);
		if (loop3(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool loop1(const vector<char> &incompleteMap, vector<char> completeMap) {
	vector<char> cache = completeMap;
	for (auto perm : perms) {
		for (int l = 0; l < 3; l++)
			setColSeg(cache, completeMap, l, perm[l]);
		if (loop2(incompleteMap, completeMap))
			return true;
	}
	return false;
}

bool solver(const vector<char> &incompleteMap, vector<char> completeMap) {
	for (int i = 0; i < 2; i++) {
		if (loop1(incompleteMap, completeMap))
			return true;
		clockwiseRotation(completeMap);
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int nuoTestCases;
	cin >> nuoTestCases;

	vector<char> previous(81);
	vector<char> current(81);

	while (nuoTestCases--) {
		char c;
		for (int i = 0; i < 81; i++) {
			cin >> c;
			previous[i] = c - '0';
		}
		for (int i = 0; i < 81; i++) {
			cin >> c;
			current[i] = c - '0';
		}

		if (solver(current, previous))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}
