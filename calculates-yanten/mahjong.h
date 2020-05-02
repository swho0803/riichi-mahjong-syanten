#pragma once

#include <string>

class Mahjong {
public:
    int Hand[34];
    std::string errInfo;

    Mahjong();
};

Mahjong read(std::string);