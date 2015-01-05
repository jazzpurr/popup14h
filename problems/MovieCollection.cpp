// Author: Jesper Norberg, jenor@kth.se
// References: http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
// https://kth.kattis.com/problems/fenwick

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <algorithm>


using namespace std;

/*
This is a FenwickTree in array form.
Think of the positions in bits. Each position stores the sum of its own value
and that of the previous indexes "contained" in its trailing zeroes.
Index 1000 (8) as such stores the sum of the values of indexes 1 to 8,
while 1001 (7) stores only the value of index 7, as it has no trailing zeroes.
We use 1-indexing for both x-values and sums.

*/
class FenwickTree{
public:
    long *fenwick;
	int treeSize;

	//constructs an empty tree
	void constructTree(int inputTreeSize){
		treeSize = inputTreeSize; //we use 1-indexing
		fenwick = new long[treeSize];
		for (int i = 0; i < treeSize; i++) {
			fenwick[i] = 0;
		}
	}

	//Adds the value (+/-) to the index as well as the upcoming sums the index is part of.
	//These will always be a one followed by trailing zeroes, starting from values above the index.
	//addToIndex(3, 1) => add 1 to indexes 3, 4, 8, 16...
	void addToIndex(int index, int addValue){
		// index += 1; //because of 1 indexing
		while (index < treeSize){
			fenwick[index] += addValue;
			index += (index & -index); //gets the last 1 in index
		}
	}

	//Sums from 1 to index.
	//Starts from the current index, and then adds the value of each 1-bit contained within i's index 
	//getSum(7) => tree[7]+tree[6]+tree[4]
	long getSum(int index){
		index -= 1; //we only want from above current
		long sum = 0;
		while (index > 0){
			sum += fenwick[index];
			index -= (index & -index); //gets the last 1 in index
		}
		return sum;
	}
};

// IO-handler. 
int main() {
	int nuoMovies, nuoChecks;
	int nuoTestCases;
	long movie, first;
	scanf("%i", &nuoTestCases);
	for (int i = 0; i < nuoTestCases; i++){
		scanf("%i %i\n", &nuoMovies, &nuoChecks);
		FenwickTree tree;
		tree.constructTree(nuoMovies+nuoChecks);
		vector<int> realIndex(nuoMovies+1); //contains "actual" positions
		first = nuoChecks; //first non-zero element in tree
		for (int j = 1; j <= nuoMovies; j++){
			realIndex[j] = nuoChecks + j;
			tree.addToIndex(realIndex[j], 1);
		}

		for (int j = 0; j < nuoChecks; j++){
			scanf("%ld ", &movie);
			int result = tree.getSum(realIndex[movie]);
			printf("%ld ", result);
			tree.addToIndex(realIndex[movie], -1);
			realIndex[movie] = first--; //put first
			tree.addToIndex(realIndex[movie], 1);			
		}
		printf("\n");
	}
	return 0;
}
