#include "general.h"

//O(log n * 10 * n) = O(n log n)

//If any prefix of any number matches an entire number, we don't have consistency 
bool isConsistent(set<string> &phoneNumbers) {
	string prefix;
	foreach(number, phoneNumbers) {
		ffor(i, 1, number.length()) {
			prefix = number.substr(0, i);
			if (phoneNumbers.find(prefix) != phoneNumbers.end()){ 
				return false;
			}
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int nuoTestCases, nuoNumbers;

	cin >> nuoTestCases;
	while (nuoTestCases--) {
		set<string> phoneNumbers;
		cin >> nuoNumbers;
		string number;
		ffor(i, 0, nuoNumbers){
			cin >> number;
			phoneNumbers.insert(number);
		}
		if (isConsistent(phoneNumbers)){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
