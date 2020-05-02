#include <fstream>
#include <array>
#include <numeric>
#include <iomanip>
#include <vector>
#include <functional>
#include <algorithm>
#include "judged.h"

template <int N>
using array = std::array<int, N>;

template <int N>
using vector = std::vector<array<N>>;

template <int N, class Function>
void generateAgariHand(int n, int m, int len, int& cnt, vector<N>& Vec, Function judge) {
    static array<N> Hand;
    if (n < N) {
        int l = len >= m ? 0 : m - len;
        int r = m >= 4 ? 4 : m;
        for (int i = l; i <= r; i++) {
            Hand[n] = i;
            generateAgariHand(n + 1, m - i, len - 4, cnt, Vec, judge);
        }
    }
    else if (judge(Hand.data())) {
        cnt++;
        Vec.push_back(Hand);
    }
}

int Distance(int x, int y) {
    return abs(x - y) + (x - y);
}

template <int N, class Iterator>
void calculate(array<N>& Hand, array<10>& ret, array<10>& amount, Iterator it) {
    int tmp = 0, syanten = 0;
    
    for (int i = 0; i < 10; i++) {
        syanten = 0x7fffffff;
        for (int j = 0; j < amount[i]; j++) {
            tmp = std::inner_product(it->begin(), it->end(), Hand.begin(), 0, std::plus<int>(), Distance) / 2;
            syanten = std::min(syanten, tmp);
            it++;
        }
        ret[i] = syanten;
    }
}

template <int N>
void makeTable(int n, array<10>& amount, vector<N>& Vec, std::ofstream& output) {
    static array<N> Hand;
    static array<10> syanten;

    if (n >= N) {
        calculate<N>(Hand, syanten, amount, Vec.begin());
        for (int i = 0; i < 10; i++)
            output << syanten[i] << " ";
        output << std::endl;
    }
    else {
        for (int i = 0; i <= 4; i++) {
            Hand[n] = i;    // encode all hands in quinary
            makeTable<N>(n + 1, amount, Vec, output);
        }
    }
}

int main() {

    array<10> kazuhaiCnt = { 0 };
    array<10> jihaiCnt = { 0 };
    // 0 to 4 is without atama, 5 to 9 otherwise
    
    vector<9> Vec1;
    vector<7> Vec2;
    // save all agari hand (9 for kazuhai, 7 for jihai)

    std::function<bool(int*)> func1 = judgeMentsu;
    std::function<bool(int*)> func2 = judgeMentsuWithAtama;
    std::function<bool(int*)> func3 = judgeKoutsu;

    std::ofstream fout1("kazuhaiTable.txt");
    std::ofstream fout2("jihaiTable.txt");

    for (int i = 0; i <= 4; i++) {
        generateAgariHand<9>(0, 3 * i, 4 * 8, kazuhaiCnt[i], Vec1, func1);
    }
    for (int i = 0; i <= 4; i++) {
        generateAgariHand<9>(0, 3 * i + 2, 4 * 8, kazuhaiCnt[i + 5], Vec1, func2);
    }
    for (int i = 0; i <= 4; i++) {
        generateAgariHand<7>(0, 3 * i, 4 * 6, jihaiCnt[i], Vec2, func3);
    }
    for (int i = 0; i <= 4; i++) {
        generateAgariHand<7>(0, 3 * i + 2, 4 * 6, jihaiCnt[i + 5], Vec2, func3);
    }

    makeTable<9>(0, kazuhaiCnt, Vec1, fout1);
    makeTable<7>(0, jihaiCnt, Vec2, fout2);

    return 0;
}