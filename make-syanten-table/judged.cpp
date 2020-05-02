#include "judged.h"

bool judgeMentsu(const int* Hand) {
    int x = Hand[0], y = Hand[1];

    for (int i = 0; i < 7; i++) {
        int d = x % 3;
        if (y >= d && Hand[i + 2] >= d) {
            x = y - d, y = Hand[i + 2] - d;
        }
        else return false;
    }
    if (x % 3 == 0 && y % 3 == 0)
        return true;
    else return false;
}

bool judgeMentsuWithAtama(int* Hand) {
    for (int i = 0; i < 9; i++) {
        if (Hand[i] >= 2) {
            if (Hand[i] -= 2, judgeMentsu(Hand))
                return Hand[i] += 2, true;
            else Hand[i] += 2;
        }
    }
    return false;
}

bool judgeKoutsu(const int* Hand) {
    int Atama = -1;

    for (int i = 0; i < 7; i++) {
        switch (Hand[i] % 3) {
            case 1:
                return false;
            case 2:
                if (Atama == -1)
                    Atama = i;
                else return true;
        }
    }
    return true;
}