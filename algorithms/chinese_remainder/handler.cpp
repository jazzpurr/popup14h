// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#define _CRT_SECURE_NO_WARNINGS

#include "general_chinese_remainder.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	int nuoTestCases;
	long long a, n, b, m;
	cin >> nuoTestCases;

	while (nuoTestCases--){
		cin >> a >> n >> b >> m;
		pair<long long, long long> answer = generalChineseRemainder(a, n, b, m);

		long long x = answer.first;
		long long K = answer.second;
		if (x == -1 && K == -1){
			printf("no solution\n");
		}
		else{
			printf("%lld %lld\n", x, K);

		}
	}

	return 0;
}