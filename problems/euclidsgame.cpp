#include "general.h"

int main(){
	LL bigN, smallN;
	bool p1sTurn;
	while (scanf("%lld%lld", &bigN, &smallN), smallN, bigN){
		if (smallN > bigN){
			swap(bigN, smallN);
		}
		p1sTurn = true;
		while (true){
			if (bigN >= 2 * smallN) break;
			bigN -= smallN;
			if (smallN > bigN){
				swap(bigN, smallN);
			}
			if (smallN == 0) break;
			p1sTurn = !p1sTurn;
		}

		if (p1sTurn) printf("Stan wins\n");
		else printf("Ollie wins\n");
	}
	return 0;
}