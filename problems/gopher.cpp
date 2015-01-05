#include "general.h"

int nuoGophers, nuoHoles, runSpeed;
double timeToDeath;


double distance(double a, double b, double c, double d){
	double e = ((a - c)*(a - c) + (b - d)*(b - d));
	return sqrt(e);
}

bool survivable(vpdd &gophers, vpdd &holes, int i, int j){
	double dist = distance(gophers[i].first, gophers[i].second, holes[j].first, holes[j].second);
	return (dist / runSpeed) <= timeToDeath;
}

bool dfs(vvi &graph, vb &visited, vb &mForGopherFound, vi &mForHoleIs, int g) {
	foreach(h, graph[g]){
		if (!visited[h]) {
			visited[h] = true;
			if (mForHoleIs[h] == -1 || dfs(graph, visited, mForGopherFound, mForHoleIs, mForHoleIs[h])) {
				mForGopherFound[g] = true;
				mForHoleIs[h] = g;
				return true;
			}
		}
	}
	return false;
}

int main() {
	double x, y;
	while (cin >> nuoGophers >> nuoHoles >> timeToDeath >> runSpeed){
		vpdd gophers(nuoGophers);
		vpdd holes(nuoHoles);
		ffor(i, 0, nuoGophers){
			scanf("%lf %lf", &x, &y);
			gophers[i] = mp(x, y);
		}
		ffor(i, 0, nuoHoles){
			scanf("%lf %lf", &x, &y);
			holes[i] = mp(x, y);
		}
		vvi graph(nuoGophers);

		ffor(i, 0, nuoGophers) {
			ffor(j, 0, nuoHoles) {
				if (survivable(gophers, holes, i, j)) {
					graph[i].pb(j);
				}
			}
		}

		int nuoSurvivors = 0;
		vb mForGopherFound(nuoGophers, false);
		vi mForHoleIs(nuoHoles, -1);

		ffor (i, 0, nuoGophers) {
			if (!mForGopherFound[i]) {
				vb visited(nuoHoles, false);
				if (dfs(graph, visited, mForGopherFound, mForHoleIs, i)){
					nuoSurvivors++;
				}
			}
		}
		printf("%d\n", nuoGophers - nuoSurvivors);
	}
	return 0;
}