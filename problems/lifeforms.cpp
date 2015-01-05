#include "general.h"

#define MAX_LEN 100200

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

bool solver(int targetLen, int stringLength) {
	vb visited(nuoLifeForms, false);
	int count;
	bool retVal = false;
	ffor(i, 1, stringLength) {
		if (lcp[i] >= targetLen) {
			ffor(j, 0, nuoLifeForms) {
				visited[j] = false;
			}
			count = 1;
			visited[wordID[suffArr[i - 1]]] = true;
			int j;
			for (j = i; (j < stringLength) && (lcp[j] >= targetLen); j++){
				if (wordID[suffArr[j]] != wordID[(suffArr[j] + targetLen - 1)]) { // switched word
					break;
				}
				if (!visited[wordID[suffArr[j]]]) {
					visited[wordID[suffArr[j]]] = true;
					count++;
				}
			}
			if (count > nuoLifeForms / 2) {
				ffor(k, 0, targetLen) {
					printf("%c", 'a' + input[suffArr[i] + k]);
				}
				printf("\n");
				retVal = true;
			}
			i = j - 1; // move forward
		}
	}
	return retVal;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	while (cin >> nuoLifeForms && nuoLifeForms != 0){
		int longestWord = -1;
		stringLength = 0;
		string line;
		ffor(i, 0, nuoLifeForms) {
			cin >> line;
			if (line.length() - longestWord > 0)
				longestWord = line.length();
			ffor(j, 0, line.length()) {
				wordID[stringLength] = i;
				input[stringLength] = line[j] - 'a';
				stringLength++;
			}
			input[stringLength] = 27 + i; //end-of-string
			stringLength++;
			input[stringLength] = 0;
		}
		stringLength--;	//we go one too far
		input[stringLength] = 0;


		if (nuoLifeForms == 1){
			cout << line;
		}

		createSuffixArray();
		createLCP();

		//solver
		int targetLen = longestWord;
		bool found = false;
		if (hasLCP) {
			while (targetLen > 0) {
				if (solver(targetLen, stringLength)) { //solution found, prints in solver
					break;
				}
				else{
					targetLen--; //keep trying with lower val
				}
			}
		}
		if (targetLen == 0){ //no solution found
			printf("?\n");
		}

		/*
		printf("\ninput:  ");
		ffor(i, 0, stringLength){
			printf(" %c ", input[i] + 'a');
		}
		printf("\nwordID: ");
		ffor(i, 0, stringLength){
			printf(" %d ", wordID[i]);
		}
		printf("\nlcp:    ");
		ffor(i, 0, stringLength){
			string tmp = to_string(lcp[i]);
			if (tmp.size() == 1){
				printf(" %d ", lcp[i]);
			}
			else{
				printf("%d ", lcp[i]);
			}
		}
		printf("\nsufArr: ");
		ffor(i, 0, stringLength){
			string tmp = to_string(suffArr[i]);
			if (tmp.size() == 1){
				printf(" %d ", suffArr[i]);
			}
			else{
				printf("%d ", suffArr[i]);
			}
		}
		printf("\nrank:   ");
		ffor(i, 0, stringLength){
			string tmp = to_string(ranking[i]);
			if (tmp.size() == 1){
				printf(" %d ", ranking[i]);
			}
			else{
				printf("%d ", ranking[i]);
			}
		}
		printf("\nindex   ");
		ffor(i, 0, stringLength){
			string tmp = to_string(suffArr[ranking[i]]);
			if (tmp.size() == 1){
				printf(" %d ", suffArr[ranking[i]]);
			}
			else{
				printf("%d ", suffArr[ranking[i]]);
			}
		}
		printf("\n");
		*/
		printf("\n");
	}
	return 0;
}
