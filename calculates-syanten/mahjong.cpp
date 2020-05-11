#include "mahjong.h"

std::string icon[34] = { "1m", "2m","3m","4m","5m","6m","7m","8m","9m",
						 "1p", "2p","3p","4p","5p","6p","7p","8p","9p",
						 "1s", "2s","3s","4s","5s","6s","7s","8s","9s",
					 	 "1z", "2z","3z","4z","5z","6z","7z"			};

Mahjong::Mahjong() {
	memset(Hand, 0, sizeof Hand);
	errInfo = "";
}

Mahjong Mahjong::set(std::string str) {
	memset(Hand, 0, sizeof Hand);
	errInfo = "";

	size_t len = str.length();

	if (isdigit(*(str.end() - 1))) {
		errInfo = "Error: Invalid input (Undefined mahjong).";
		return *this;
	}

	int nowType = -1, mahjongCnt = 0;
	for (size_t i = str.length() - 1; ~i; i--) {
		if (!isdigit(str[i])) {
			char nowMahjong = tolower(str[i]);
			switch (nowMahjong) {
				case 'm': nowType = 0; break;
				case 'p': nowType = 1; break;
				case 's': nowType = 2; break;
				case 'z': nowType = 3; break;
				default: errInfo = (std::string)"Error: Invalid input (Undefined type '" + nowMahjong + "').";
						 return *this;
			}
		}
		if (isdigit(str[i])) {
			int nowMahjong = (int)str[i] - '0';
			if (nowMahjong == 0)
				nowMahjong = 5;
			int m = nowType * 9 + nowMahjong - 1;
			Hand[m]++, mahjongCnt++;
			if (Hand[m] > 4) {
				errInfo = "Error: Invalid input (Overmuch '" + icon[m] + "').";
				return *this;
			}
		}
	}

	if (mahjongCnt != 14) {
		errInfo = "Error: Invalid input (Incorrect number " + std::to_string(mahjongCnt) + ").";
		return *this;
	}
	
	return *this;
}

bool Mahjong::operator!() {
	if (errInfo == "")
		return false;
	else return true;
}

void Mahjong::printErrInfo() {
	std::cout << errInfo << std::endl << std::endl;
}

int* Mahjong::getHand() {
	return Hand;
}