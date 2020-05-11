#include "syanten.h"

Syanten::Syanten() : kazuhaiTable(std::vector<Vector>((int)std::pow(5, 9), Vector(10))),
					 jihaiTable(std::vector<Vector>((int)std::pow(5, 7), Vector(10))) {
	initTable(kazuhaiTable.begin(), kazuhaiTable.end(), "kazuhai-table.txt");
	initTable(jihaiTable.begin(), jihaiTable.end(), "jihai-table.txt");
}

Pair Syanten::operator()(Mahjong t) {
	int* Hand = t.getHand();
	int normal = calculateNormal(Hand) - 1;
	int standard = std::min(calculateKokushi(Hand), calculateChitoi(Hand)) - 1;
	return std::make_pair(normal, standard);
}

int Syanten::calculateNormal(const int* Hand) const {
	Vector tmp = kazuhaiTable[quinaryConverter(Hand, 0)];
	update1(tmp, kazuhaiTable[quinaryConverter(Hand, 9)]);
	update1(tmp, kazuhaiTable[quinaryConverter(Hand, 18)]);
	update2(tmp, jihaiTable[quinaryConverter(Hand, 27)]);
	return tmp[9];
}

int Syanten::calculateChitoi(const int* Hand) const {
	int kind = 0, pair = 0;

	for (int i = 0; i < 34; i++) {
		if (Hand[i] > 0)
			kind++;
		if (Hand[i] >= 2)
			pair++;
	}

	return 7 - pair + (kind < 7 ? 7 - kind : 0);
}

int Syanten::calculateKokushi(const int* Hand) const {
	int kind = 0, pair = 0;
	int Orphans[] = { 0,8,9,17,18,26,27,28,29,30,31,32,33 };

	for (int i : Orphans) {
		if (Hand[i] > 0)
			kind++;
		if (Hand[i] >= 2)
			pair++;
	}

	return 14 - kind - (pair > 0 ? 1 : 0);
}

void Syanten::update1(Vector& ret, const Vector& tbl) const {
	for (int i = 9; i >= 5; i--) {
		int syanten = std::min(ret[i] + tbl[0], ret[0] + tbl[i]);
		for (int j = 5; j < i; j++)
			syanten = std::min({ ret[j] + tbl[i - j],ret[i - j] + tbl[j],syanten });
		ret[i] = syanten;
	}
	for (int i = 4; i >= 0; i--) {
		int syanten = ret[i] + tbl[0];
		for (int j = 0; j < i; j++)
			syanten = std::min(ret[j] + tbl[i - j], syanten);
		ret[i] = syanten;
	}
}

void Syanten::update2(Vector& ret, const Vector& tbl) const {
	int syanten = std::min(ret[9] + tbl[0], ret[0] + tbl[9]);
	for (int i = 5; i < 9; i++) {
		syanten = std::min({ ret[i] + tbl[9 - i],ret[9 - i] + tbl[i],syanten });
	}
	ret[9] = syanten;
}

int quinaryConverter(const int* Hand, int pos) {
	int step = pos > 26 ? 7 : 9;
	return std::accumulate(Hand + pos + 1, Hand + pos + step, Hand[pos], [](int x, int y) {return 5 * x + y; });
}