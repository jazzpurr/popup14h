// Author: Jesper Norberg, jenor@kth.se
// References: http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
// https://kth.kattis.com/problems/fenwick

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>


using namespace std;

// IO-handler. 
int main() {
	int tmp, toSell, nuoJackCDs, nuoJillCDs;
	scanf("%i %i\n", &nuoJackCDs, &nuoJillCDs);
	while (nuoJackCDs != 0 && nuoJillCDs != 0){
		unordered_set<int> jackCDs(nuoJackCDs);
		for (int i = 0; i < nuoJackCDs; ++i){
			scanf("%i", &tmp);
			jackCDs.insert(tmp);
		}
		toSell = 0;
		for (int i = 0; i < nuoJillCDs; ++i){
			scanf("%i", &tmp);
			if (jackCDs.end() != jackCDs.find(tmp)){
				++toSell;
			}
		}
		printf("%i\n", toSell);		
		scanf("%i %i\n", &nuoJackCDs, &nuoJillCDs);
	}
	return 0;
}
