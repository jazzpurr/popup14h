#include "general.h"

int solver(int n){
	int div = 1;
	int count = 1;
	while (div > 0){
		if (div < n){
			count++;
			div = 10 * div + 1;
		}
		div %= n;
	}
	return count;
}

int main(){
	int n;
	while (scanf("%d", &n) != EOF){
		int answer = solver(n);
		printf("%d\n", answer);
	}

	return 0;
}