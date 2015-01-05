#include "general.h"

LL nuoZeroesIn(LL v) {
	if (v < 0){ //m == 0
		return 0;
	}
	LL count = 1;
	for (LL mul = 1; mul * 10 <= v; mul *= 10) {
		LL west = v / mul;
		LL east = v % mul;
		LL last = west % 10;
		//printf("west: %lld, east: %lld, last %lld\n", west, east, last);
		if (last == 0) {
			count += (((west / 10) - 1) * mul) + east + 1;
		}
		else {
			count += (west / 10) * mul;
		}
	}
	//printf("count %lld: %lld\n", v, count);
	return count;
}

int main() {
	LL m, n;
	while (scanf("%lld %lld", &m, &n), m >= 0) {
		printf("%lld\n", nuoZeroesIn(n) - nuoZeroesIn(m - 1));
	}
	return 0;
}
