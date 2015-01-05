#include<iostream>
#include<string>

using namespace std;

bool isNecklace(string s){
	string tmp;
	int nuoBits = s.size();

	for (int i = 1; i < nuoBits; ++i){ //for each potential cycle of s
		tmp = s.substr(i, nuoBits - i) + s.substr(0, i);
		if (tmp < s) return false; //trololo
	}

	return true;
}

void solver(string input){
	int nuoBits = input.size();

	int start = 0;
	while (start < nuoBits){ //for each necklace in input
		for (int len = nuoBits - start; len >= 0; --len){ //find longest necklace from start
			string tmp = input.substr(start, len); // from index start and len chars forward
			if (isNecklace(tmp)){
				cout << "(" << tmp << ")";
				start = start + len;
				break;
			}
		}
	}
	cout << endl;
}

int main(){
	int nuoTestCases;
	string input;
	cin >> nuoTestCases;

	for (int i = 0; i < nuoTestCases; ++i){
		cin >> input;
		solver(input);
	}

	return 0;
}