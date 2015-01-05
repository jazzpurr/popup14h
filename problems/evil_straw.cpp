#include "general.h"

#define alhpSize 26 //a-z

int solver(string &input) {
	int length = input.size();
	int i, j, k;
	int l, r;
	int nuoSwaps = 0;
	ffor(i, 0, length / 2){
		j = length - 1 - i;
		if (input[i] != input[j]){
			for (l = i; input[l] != input[j]; l++);
			for (r = j; input[r] != input[i]; r--);
			if ((l - i) < (j - r)){
				nuoSwaps = nuoSwaps + l - i;
				rfor(k, l, i){
					input[k] = input[k - 1];
				}
			}
			else{
				nuoSwaps = nuoSwaps + j - r;
				ffor(k, r, j){
					input[k] = input[k + 1];
				}
			}
		}
	}
	return nuoSwaps;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int nuoTestCases;
	string input;
	cin >> nuoTestCases;
	while (nuoTestCases--){
		cin >> input;
		int nuoOddLetters = 0;
		int length = input.size();
		char ch;
		vi letters(alhpSize, 0);
		ffor(i, 0, length){
			letters[input[i] - 'a']++;
		}
		ffor(i, 0, alhpSize){
			if (letters[i] % 2){
				nuoOddLetters++;
			}
		}
		if (nuoOddLetters <= 1){ //solvable if 1 or 0 odd letters
			int nuoSwaps = solver(input);
			cout << nuoSwaps << endl;
		}
		else{
			cout << "Impossible" << endl;
		}
	}
	return 0;
}