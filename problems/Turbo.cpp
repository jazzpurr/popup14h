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
		//index -= 1; //we only want from above current
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
	int nuoElements, tmp;
	scanf("%i", &nuoElements);
	FenwickTree tree;
	tree.constructTree(nuoElements + 1);
	vector<int> index(nuoElements + 1); //contains "actual" positions
	for (int i = 1; i <= nuoElements; ++i){
		scanf("%i ", &tmp);
		index[tmp] = i;
	}
	int nuoSwitches;
	for (int i = 1; i <= nuoElements / 2; ++i){
		//position we want to move to == i
		nuoSwitches = index[i] - 1 - tree.getSum(index[i]);
		printf("%i\n", nuoSwitches);
		tree.addToIndex(index[i], 1);
		//printf("index1: %i\n", index[i]);
		//printf("tree1: %i\n", tree.getSum(index[i]));

		tmp = nuoElements - i + 1; //position we want to move to
		nuoSwitches = nuoElements - index[tmp] - tree.getSum(nuoElements) + tree.getSum(index[tmp]);
		printf("%i\n", nuoSwitches);
		tree.addToIndex(index[tmp], 1);
		//printf("index2: %i\n", index[tmp], nuoElements);
		//printf("tree1: %i, tree2: %i\n", tree.getSum(nuoElements), tree.getSum(index[tmp]));
	}

	if (nuoElements % 2 != 0) { //udda
		printf("0\n");
	}
	return 0;
}
