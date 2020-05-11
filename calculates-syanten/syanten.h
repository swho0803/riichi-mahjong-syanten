#pragma once

#include <numeric>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include "mahjong.h"

using Vector = std::vector<int>;
using Iterator = std::vector<Vector>::iterator;
using Pair = std::pair<int, int>;

class Syanten {
public:
	Syanten();
	int calculateChitoi(const int*) const;
	int calculateKokushi(const int*) const;
	int calculateNormal(const int*) const;
	Pair operator()(Mahjong);

	void update1(Vector&, const Vector&) const;
	void update2(Vector&, const Vector&) const;

private:
	Iterator it1, it2;
	std::vector<Vector> kazuhaiTable;
	std::vector<Vector> jihaiTable;
	Iterator initTable(Iterator, Iterator, const char*) const;
};

int quinaryConverter(const int*, int);