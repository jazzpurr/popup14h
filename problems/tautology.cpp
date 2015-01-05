#include "general.h"

char str[101];
int len;

bool solver(){
	bool list[101];
	for (int P = 0; P <= 1; P++){
		for (int Q = 0; Q <= 1; Q++){
			for (int R = 0; R <= 1; R++){
				for (int S = 0; S <= 1; S++){
					for (int T = 0; T <= 1; T++){
						int top = 0;
						for (int i = len - 1; i >= 0; i--){
							if (str[i] == 'p'){
								list[top++] = P;
							}
							else if (str[i] == 'q'){
								list[top++] = Q;
							}
							else if (str[i] == 'r'){
								list[top++] = R;
							}
							else if (str[i] == 's'){
								list[top++] = S;
							}
							else if (str[i] == 't'){
								list[top++] = T;
							}
							else if (str[i] == 'K'){
								top--;
								list[top - 1] = (list[top - 1] && list[top]);
							}
							else if (str[i] == 'A'){
								top--;
								list[top - 1] = (list[top - 1] || list[top]);
							}
							else if (str[i] == 'N'){
								list[top - 1] = !list[top - 1];
							}
							else if (str[i] == 'C'){
								top--;
								list[top - 1] = (!list[top - 1] || list[top]);
							}
							else if (str[i] == 'E'){
								top--;
								list[top - 1] = (list[top - 1] == list[top]);
							}
						}
						if (top != 1 || list[top - 1] != 1){
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

int main(){
	while (cin >> str){
		if (str[0] == '0'){
			break;
		}
		len = strlen(str);
		if (solver()){
			cout << "tautology" << endl;
		}
		else{
			cout << "not" << endl;
		}
	}
	return 0;
}