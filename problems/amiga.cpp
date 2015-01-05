#include "general.h"

struct Fact {
	int p1_type, p1;
	int p2_type, p2;
	int relation;
	Fact() { }
};

int amigaPerson;
int roomTypeProp[5][6];     // roomTypeProp[roomNo][propType] => property (-1 == unknown)
int typePropRoom[6][5]; // typePropRoom[propType][prop] => room (-1 == unknown)

vector<Fact*> propFacts[6][5]; // propFacts[type][prop] => facts concerning typeProp

string props[] = {
	"1", "2", "3", "4", "5",
	"blue", "green", "red", "white", "yellow",
	"anna", "bernhard", "chris", "david", "ellen",
	"danish", "finnish", "icelandic", "norwegian", "swedish",
	"amiga", "atari", "linux", "mac", "windows",
	"c", "c++", "java", "pascal", "perl" };

bool check(vector<Fact*> v) {
	for (int i = 0; i < v.size(); i++) {
		int r1 = typePropRoom[v[i]->p1_type][v[i]->p1];
		int r2 = typePropRoom[v[i]->p2_type][v[i]->p2];
		if (r1 >= 0 && r2 >= 0) {
			switch (v[i]->relation) {
			case 0: if (r1 != r2) return false; break;
			case 1: if (r2 - r1 != 1) return false; break;
			case 2: if (r1 - r2 != 1) return false; break;
			case 3: if (r1 - r2 != 1 && r2 - r1 != 1) return false; break;
			}
		}
	}
	return true;
}

bool solver(){
	if (amigaPerson >= 0 && typePropRoom[4][0] >= 0 && roomTypeProp[typePropRoom[4][0]][2] == amigaPerson){
		return false;
	}

	int best = -1, type, prop;
	for (int i = 1; i < 6; i++){
		for (int j = 0; j < 5; j++){
			if (typePropRoom[i][j] < 0) {
				int poss = 0;
				for (int k = 0; k < 5; k++){
					if (roomTypeProp[k][i] < 0) {
						typePropRoom[i][j] = k;
						if (check(propFacts[i][j])) poss++;
						typePropRoom[i][j] = -1;
					}
				}
				if (!poss) return false;
				if (best < 0 || poss < best) {
					best = poss;
					type = i;
					prop = j;
				}
			}
		}
	}
	if (best < 0) {
		int person = roomTypeProp[typePropRoom[4][0]][2];
		if (amigaPerson >= 0 && amigaPerson != person) {
			amigaPerson = -1; // Multiple answers
			return true;
		}
		amigaPerson = person;
		return false; // Look for multiple answers
	}

	for (int k = 0; k < 5; k++){
		if (roomTypeProp[k][type] < 0) {
		typePropRoom[type][prop] = k;
		if (check(propFacts[type][prop])) {
			roomTypeProp[k][type] = prop;
			if (solver()) return true;
			roomTypeProp[k][type] = -1;
		}
		typePropRoom[type][prop] = -1;
		}
	}
	return false;
}

int main() {
	int nuoTestCases, nuoFacts;
	string p1, r, p2;
	cin >> nuoTestCases;

	for (int scenarioNo = 1; scenarioNo <= nuoTestCases; scenarioNo++) {
		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 5; j++) {
				propFacts[i][j].clear();
				roomTypeProp[j][i] = i ? -1 : j;
				typePropRoom[i][j] = i ? -1 : j;
			}
		}

		cin >> nuoFacts;
		vector<Fact*> facts(nuoFacts);
		vector<vector<vvi>> alreadyUsed(6, vector<vvi>(5, vvi(6, vi(4, -1)))); //type1, p1, type2, rel => p2 
		for (int i = 0; i < nuoFacts; i++) {
			cin >> p1 >> r >> p2;
			Fact *f = new Fact();
			facts[i] = f;
			f->p1 = f->p2 = f->relation = -1;
			for (int j = 0; j < 30; j++) {
				if (p1 == props[j]){
					f->p1_type = j / 5;
					f->p1 = j % 5;
					propFacts[f->p1_type][f->p1].push_back(f);
				}
				if (p2 == props[j]){
					f->p2_type = j / 5;
					f->p2 = j % 5;
					propFacts[f->p2_type][f->p2].push_back(f);
				}
			}
			if (r == "same-as") f->relation = 0;
			else if (r == "left-of") f->relation = 1;
			else if (r == "right-of") f->relation = 2;
			else if (r == "next-to") f->relation = 3;
		}

		cout << "scenario #" << scenarioNo << ": ";

		amigaPerson = -2;
		if (check(facts)){
			solver();
		}
		if (amigaPerson == -1)
			cout << "cannot identify the amiga owner." << endl;
		else if (amigaPerson == -2)
			cout << "impossible." << endl;
		else
			cout << props[amigaPerson + 10] << " owns the amiga." << endl;

		for (int i = 0; i < facts.size(); i++){
			delete facts[i];
		}
	}

	return 0;
}