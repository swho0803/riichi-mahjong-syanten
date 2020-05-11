#include "syanten.h"

Iterator Syanten::initTable(Iterator begin, Iterator end, const char* fileName) const {
	std::ifstream input(fileName);
	Vector tmp(10);

	while (begin != end) {
		for (int i = 0; i < 10; i++)
			input >> tmp[i];
		*begin++ = tmp;
	}
	return begin;
}