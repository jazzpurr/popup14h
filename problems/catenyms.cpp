#include "general.h"

#define nuoLetters 26

struct Edge{
	int to, next;
	int index;
	bool visited;
};

void addEdge(vector<Edge> &edges, vi &wordIndices, int u, int v, int index, int wordIdx){
	edges[wordIdx].to = v;
	edges[wordIdx].next = wordIndices[u];
	edges[wordIdx].index = index;
	edges[wordIdx].visited = false;
	wordIndices[u] = wordIdx;
}

void dfs(vector<Edge> &edges, vi &head, vi &answer, int u){
	for (int i = head[u]; i != -1; i = edges[i].next){
		if (!edges[i].visited){
			edges[i].visited = true;
			dfs(edges, head, answer, edges[i].to);
			answer.pb(edges[i].index);
		}
	}
}
int main()
{

	int nuoTestCases, nuoWords;
	scanf("%d", &nuoTestCases);
	while (nuoTestCases--) {
		scanf("%d", &nuoWords);
		vs strings(nuoWords);
		vector<Edge> edges(nuoWords);
		vi answer;
		vi wordIndices(nuoLetters, -1);

		for (int i = 0; i < nuoWords; i++){
			cin >> strings[i];
		}
		sort(all(strings)); //in ascending order

		vi inC(nuoLetters, 0);
		vi outC(nuoLetters, 0);
		int start = strings[0][0] - 97;
		int wordIdx = 0;
		//letters indexed a = 0 to z = 25
		rfor(i, nuoWords, 0){
			int u = strings[i][0] - 97;     //first letter in word string[i]
			int v = strings[i][strings[i].length() - 1] - 97; //last letter in word string[i]
			outC[u]++;
			inC[v]++;
			addEdge(edges, wordIndices, u, v, i, wordIdx);
			wordIdx++;
		}


		bool unsolvable = false;

		int counter1 = 0, counter2 = 0;
		ffor(i, 0, nuoLetters){
			if (outC[i] - inC[i] == 1) {
				counter1++;
				start = i;
			}
			else if (outC[i] - inC[i] == -1){
				counter2++;
			}
			else if (outC[i] - inC[i] != 0){
				counter1 = -1; //impossible
			}
		}

		if (!((counter1 == 0 && counter2 == 0) || (counter1 == 1 && counter2 == 1))){
			unsolvable = true;
		}
		if (!unsolvable){
			dfs(edges, wordIndices, answer, start);
		}
		if (answer.size() != nuoWords){
			unsolvable = true;
		}
		if (unsolvable){
			printf("***\n");
		}

		else{
			rfor(i, nuoWords, 1){
				cout << strings[answer[i]] << ".";
			}
			cout << strings[answer[0]] << endl;
		}
	}
	return 0;
}