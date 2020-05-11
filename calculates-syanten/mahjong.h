#pragma once

#include <string>
#include <iostream>

class Mahjong {
public:
	Mahjong();
	Mahjong set(std::string);
	bool operator!();
	void printErrInfo();
	int* getHand();

private:
	int Hand[34];
	std::string errInfo;
};