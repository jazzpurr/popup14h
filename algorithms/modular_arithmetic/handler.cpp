// Authors:
// Jesper Norberg, jenor@kth.se
// Didrik Nordström, didrikn@kth.se

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "modular.h"

using namespace std;

//Source: http://en.wikipedia.org/wiki/Modular_arithmetic

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	long long a = -3;
	long long b = 2;

	long long m, nuoOperations;
	long long x, y;
	string op;
	cin >> m >> nuoOperations;
	while (m != 0){
		for (long long i = 0; i < nuoOperations; i++){
			cin >> x >> op >> y;
			if (op == "+"){
				printf("%d\n", add_mod(x, y, m));
			}
			else if (op == "-"){
				printf("%d\n", sub_mod(x, y, m));
			}
			else if (op == "*"){
				printf("%d\n", mul_mod(x, y, m));
			}
			else if (op == "/"){
				printf("%d\n", div_mod(x, y, m));
			}
			else{
				printf("Invalid input\n");
			}
		}
		cin >> m >> nuoOperations;
	}
	return 0;
}