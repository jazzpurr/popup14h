// Author: Jesper Norberg, jenor@kth.se
// https://kth.kattis.com/problems/knapsack

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> knapsack01(string* items, int* values, int* weights, int nuoObjects, int capacity);

int main() {
    // IO performance enhancements
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	float input;
	int nuoObjects;
	int capacity;
	cin >> input;
	while (cin.good()){
		cin >> nuoObjects;
		capacity = (int)input; //remove decimal
		string *items = new string[nuoObjects];
		int *values = new int[nuoObjects];
		int *weights = new int[nuoObjects];
		for (int i = 0; i < nuoObjects; i++) {
			items[i] = to_string(i);
			cin >> values[i] >> weights[i];
		}
		vector<string> results = knapsack01(items, values, weights, nuoObjects, capacity);
		cout << results.size() << endl;
		for (string i : results){
			cout << i << " ";
		}
		cout << endl;
		delete[] items;
		delete[] values;
		delete[] weights;

		cin >> input;
	}
	return 0;
}

// Creates a (nuoObjects+1)*(weight+1) matrix where each position stores the optimal value for that weight w using
// only the objects from 1 to i. As such, the bottom right corner will store the optimal value using the
// maximum weight and all objects. We will then have to backtrack in order to find the path we took.

vector<string> knapsack01(string* items, int* values, int* weights, int nuoObjects, int capacity){
	vector<string> results;
	//allocate the array
	int i, w;
	int** matrix = new int*[nuoObjects + 1];
	for (int i = 0; i <= nuoObjects; i++){
		matrix[i] = new int[capacity + 1];
	}

	for (i = 0; i <= nuoObjects; i++)
	{
		for (w = 0; w <= capacity; w++)
		{
			if (i == 0 || w == 0){
				matrix[i][w] = 0;
			}
			else if (weights[i - 1] <= w){
				//max value of using current object or not using it. 
				matrix[i][w] = max(matrix[i - 1][w - weights[i - 1]] + values[i - 1], matrix[i - 1][w]);
			}
			else{
				//we don't currently have the capacity for this object
				matrix[i][w] = matrix[i - 1][w];
			}
		}
	}

	// Backtracking
	i = nuoObjects;
	w = capacity;
	while (i >0 && w > 0)
	{
		if (matrix[i][w] == matrix[i - 1][w]) //object i wasn't used, same capacity remaining
		{
			i = i - 1;
			continue;
		}
		else
		{
			results.push_back(items[i - 1]); //object i was used, only w-weights[i] capacity remains
			i = i - 1;
			w = w - weights[i];
		}
	}

	for (i = 0; i <= nuoObjects; i++)
		delete[] matrix[i];
	delete[] matrix;

	return results;
}
