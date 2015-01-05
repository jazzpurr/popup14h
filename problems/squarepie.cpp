#include "general.h"

typedef tuple<long, long, long> tlll;
typedef set<tlll> stlll; //yeah baby!

// if horizontal split: divide into top/bot recursions
// else if vertical split: divide into right/left recursions
// else: area divided completely: add to answer
// 
void solver(long x1, long x2, long y1, long y2, vl &answer, stlll &horLines, stlll &verLines) {
	// check for horizontal split
	auto botBorder = horLines.upper_bound(make_tuple(x1, x2, y1)); //above y1
	auto topBorder = horLines.lower_bound(make_tuple(x1, x2, y2)); //below or equal to y2
	if (botBorder != topBorder) { // horizontal split found
		long split = get<2>(*botBorder); // grab first split from the bottom
		solver(x1, x2, y1, split, answer, horLines, verLines);
		solver(x1, x2, split, y2, answer, horLines, verLines);
	}
	else{
		// check for vertical split
		auto leftBorder = verLines.upper_bound(make_tuple(y1, y2, x1)); //right of x1
		auto rightBorder = verLines.lower_bound(make_tuple(y1, y2, x2)); // left of or equal to x2
		if (leftBorder != rightBorder) { // vertical split found
			long split = get<2>(*leftBorder); // grab first split from the left
			solver(x1, split, y1, y2, answer, horLines, verLines);
			solver(split, x2, y1, y2, answer, horLines, verLines);
		}
		else{
			// area completely divided, add to answer
			answer.push_back((x2 - x1) * (y2 - y1));
		}
	}
}

int main() {
	int nuoLines;
	scanf("%d", &nuoLines);

	//will contain all the lines in the square
	stlll horLines;
	stlll verLines;

	long x1, y1, x2, y2;

	// these will cover the entire square area
	long minX = numeric_limits<long>::max();
	long maxX = numeric_limits<long>::min();
	long minY = numeric_limits<long>::max();
	long maxY = numeric_limits<long>::min();

	ffor(i, 0, nuoLines){
		scanf("%ld %ld %ld %ld", &x1, &y1, &x2, &y2);

		// swap so that x1 < x2, y1 < y2
		if (x1 > x2){
			swap(x1, x2);
		}
		if (y1 > y2){
			swap(y1, y2);
		}

		minX = min(minX, x1);
		maxX = max(maxX, x2);
		minY = min(minY, y1);
		maxY = max(maxY, y2);

		if (x1 == x2){
			verLines.insert(make_tuple(y1, y2, x1));
		}
		else { //y1 == y2
			horLines.insert(make_tuple(x1, x2, y1));
		}
	}
	vl answer;
	solver(minX, maxX, minY, maxY, answer, horLines, verLines); // finds the areas
	sort(answer.begin(), answer.end(), greater<long>()); // output in descending order

	// print area as fraction
	double total_area = (maxX - minX) * (maxY - minY);
	foreach(area, answer){
		printf("%.9lf\n", area / total_area);
	}

	return 0;
}
