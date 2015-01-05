#include "general.h"

#define MAX_LEN 200010

int input[MAX_LEN], ranking[MAX_LEN], suffArr[MAX_LEN], lcp[MAX_LEN], wordID[MAX_LEN];
int pos[MAX_LEN], tmp[MAX_LEN];
int nuoLifeForms, stringLength, it;
bool hasLCP = false;

// O(n log^2 n)
// source: TopCoder forums

// sa = The suffix array. Contains the n suffixes of combinedS sorted lexicographically, 
// represented by starting position in string
// ranking = inverse of suffixArray, ranking[i] = index of suffix[i...n]
// as such, sa[i] = k <==> ranking[k] = i.
// This allows comparing suffixes in O(1), as suffix[i...n] < suffix[j...n] if ranking[i]<rank[j]


bool comp(int i, int j) {
	if (pos[i] == pos[j]) {
		i += it;
		j += it;
		if ((i < stringLength) && (j < stringLength)){
			return pos[i] < pos[j];
		}
		else{
			return i > j;
		}
	}
	return pos[i] < pos[j];
}


void createSuffixArray() {
	ffor(i, 0, stringLength) {
		pos[i] = input[i];
		suffArr[i] = i;
		tmp[i] = 0;
	}

	it = 1;

	// breaks when all 2it-grams are different
	while (true) {
		// use it-1 pos (pos of 2^(it-1)-grams) to sort 2^it-grams 
		sort(begin(suffArr), begin(suffArr) + stringLength, comp);

		// lexographic renaming => store the pos of each gram in the sorted bigrams (suffArr)
		ffor(i, 0, stringLength - 1) {
			bool higher = comp(suffArr[i], suffArr[i + 1]);     //since suffArr is sorted, increment pairwise
			tmp[i + 1] = tmp[i] + higher;
		}
		//update pos
		ffor(i, 0, stringLength) {
			pos[suffArr[i]] = tmp[i];
		}
		if (tmp[stringLength - 1] >= stringLength - 1) {
			break;
		}
		it = it << 1; //checking for 2^(it+1)-grams next iteration
	}
}

// LCP[i] = length of the longest common prefix of suffArr[i] and suffArr[i-1]
void createLCP() {
	ffor(i, 0, stringLength) {
		ranking[suffArr[i]] = i;
	}
	lcp[0] = 0;
	int h = 0;
	ffor(i, 0, stringLength) {
		if (ranking[i] == 0) {
			lcp[i] = 0;
			continue;
		}
		if (ranking[i] > 0) {
			int j = suffArr[ranking[i] - 1];
			while (i + h < stringLength && j + h < stringLength && input[i + h] == input[j + h]){
				h++;
			}
			lcp[ranking[i]] = h;
			if (h > 0) {
				h--;
				hasLCP = true;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> stringLength;
	string line;
	cin >> line;
	ffor(i, 0, stringLength) {
		input[i] = line[i] - 'a';
	}
	input[stringLength] = 0;
	createSuffixArray();
	createLCP();
	int longest = 0;
	ffor(i, 0, stringLength + 1) {
		longest = max(longest, lcp[i]);
	}
	cout << longest << endl;
}
