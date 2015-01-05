#include "general.h"

int main(){
	int nuoStones, nuoValues;
	while (scanf("%d%d", &nuoStones, &nuoValues) != EOF){
		vi values(nuoValues, 0);
		vb p1Wins(nuoStones+1, false);
		ffor(i, 0, nuoValues){
			scanf("%d", &values[i]);
		}
		ffor(i, 1, nuoStones + 1){
			ffor(j, 0, nuoValues){
				if (i - values[j] >= 0 && !p1Wins[i - values[j]]){
					p1Wins[i] = true;
					break;
				}
			}
		}
		if (p1Wins[nuoStones]){
			printf("Stan wins\n");
		}
		else {
			printf("Ollie wins\n");
		}
	}
	return 0;
}