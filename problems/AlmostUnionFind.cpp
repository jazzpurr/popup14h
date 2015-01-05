// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se
//
// https://kth.kattis.com/problems/unionfind

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <set>

using namespace std;


// Solves the union-find problem
int main() {

	int nuoElements; // Elements in the base set
	int nuoOps; // Number of operations
	int op, p, q; // Current operands
	
	while (scanf("%i %i", &nuoElements, &nuoOps) != EOF){

		vector<set<int>> sets(nuoElements + 1);
		vector<int> sums(nuoElements + 1);
		vector<int> parents(nuoElements + 1);

		for (int i = 1; i <= nuoElements; i++){
			sets[i].insert(i);
			parents[i] = i;
			sums[i] = i;
		}

		for (int i = 0; i < nuoOps; i++){
			//for (int i = 1; i <= nuoElements; i++){
			//	fprintf(stderr, "parents[i]: %i\n", parents[i]);
			//}
			//fprintf(stderr, "------------\n");

			scanf("%i", &op); // Read operator and operands
			if (op == 1){ //union
				scanf("%i %i", &p, &q);
				int P = parents[p];
				int Q = parents[q];
				if (P != Q){
					for (const int &j : sets[P]){
						sets[Q].insert(j);
						parents[j] = Q;
					}
					sums[Q] += sums[P];
					sums[P] = 0;
					sets[P].clear();
				}
			}
			else if (op == 2){ //move
				scanf("%i %i", &p, &q);
				int P = parents[p];
				int Q = parents[q];
				if (P != Q){
					sums[P] -= p;
					sums[Q] += p;
					sets[P].erase(p);
					sets[Q].insert(p);
					parents[p] = Q;
					if (P == p && !sets[P].empty()){
						int tmpSum = sums[P];
						sums[P] = 0;
						int oldP = P;
						P = *sets[P].begin();
						sums[P] = tmpSum;
						sets[P] = sets[oldP];
						sets[oldP].clear();
						for (const int &j : sets[P]){
							parents[j] = P;
						}
					}
				}
			}
			else if (op == 3){ //sum
				scanf("%i", &p);
				printf("%i %i\n", sets[parents[p]].size(), sums[parents[p]]);
			}
		}
	}
	return 0;
}