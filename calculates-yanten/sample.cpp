#include <iostream>
#include "syanten.h"
#include "mahjong.h"

using Pair = std::pair<int, int>;

int main() {

    Syanten runner;
    std::cout << "初始化完毕！" << std::endl;

    Mahjong cur;
    std::string str;

    while (std::cout << "input: " && std::cin >> str) {
        cur = read(str);

        if (cur.errInfo != "") {
            std::cout << cur.errInfo << std::endl;
            continue;
        }

        Pair result = runner(cur.Hand);
        std::cout << "一般型向听数: " << result.first << std::endl;
        std::cout << "标准型向听数: " << result.second << std::endl;
        std::cout << std::endl;
    }

    return 0;
}