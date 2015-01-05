#include "general.h"
#include "modular.h"

int gcd(int a, int b){
	if (b == 0){
		return a;
	}
	return gcd(b, a % b);
}

int lcm(int a, int b){
	return a*b / gcd(a, b);
}

int exp_mod(int a, int b, int c){
	int res = 1;
	int t = a % c;

	while (b > 0){
		if (b & 1){
			res = res*t%c;
		}
		t = t*t % c;
		b >>= 1;
	}
	return res;
}

int gauss(int p, int strLen, vvi &matrix, vi &result){
	int row, col;
	row = col = 0;

	while (row < strLen && col < strLen){
		int maxRow = row;
		ffor(i, row + 1, strLen){
			if (abs(matrix[i][col]) > abs(matrix[maxRow][col])){
				maxRow = i;
			}
		}
		if (maxRow != row){
			ffor(j, col, strLen + 1){
				swap(matrix[row][j], matrix[maxRow][j]);
			}
		}
		if (matrix[row][col] == 0){
			col++;
			continue;
		}

		ffor(i, row + 1, strLen){
			if (matrix[i][col] == 0) continue;

			int l = lcm(abs(matrix[i][col]), abs(matrix[row][col]));
			int a = l / matrix[i][col];
			int b = l / matrix[row][col];
			if (matrix[i][col] * matrix[row][col] < 0) {
				b = -b;
			}

			ffor(j, col, strLen + 1){
				matrix[i][j] = ((matrix[i][j] * a - matrix[row][j] * b) % p + p) % p;
			}
		}
		row++;
		col++;
	}
	ffor(i, row, strLen){
		if (matrix[i][strLen] != 0){
			return -1;
		}
	}
	if (row < strLen){
		return strLen - row;
	}
	rfor(i, strLen - 1, 0){
		int tmp = matrix[i][strLen];
		ffor(j, i + 1, strLen){
			tmp = ((tmp - matrix[i][j] * result[j]) % p + p) % p;
		}
		while (tmp % matrix[i][i] != 0){
			tmp += p;
		}
		result[i] = (tmp / matrix[i][i]) % p;
	}
	return 0;
}

int main(){
	int nuoTestCases, p;
	char input[80];

	scanf("%d", &nuoTestCases);
	while (nuoTestCases--){
		scanf("%d %s", &p, input);
		int strLen = strlen(input);

		vvi matrix(strLen + 1, vi(strLen + 1));

		ffor(i, 0, strLen){
			if (input[i] == '*'){
				matrix[i][strLen] = 0;
			}
			else {
				matrix[i][strLen] = input[i] - 'a' + 1;
			}

			ffor(j, 0, strLen){
				matrix[i][j] = exp_mod(i + 1, j, p);
			}
		}
		vi result(strLen);
		gauss(p, strLen, matrix, result);

		ffor(i, 0, strLen){
			printf("%d ", result[i]);
		}
		printf("\n");
	}
	return 0;
}