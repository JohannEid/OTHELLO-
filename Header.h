//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_HEADER_H
#define OTHELLO_HEADER_H

#include "bits/stdtr1c++.h"
#include "rlutil.h"
#include <SFML/Graphics.hpp>

inline void clearconsole() {
    for (int i{0}; i < 20; ++i)
        std::cout << std::endl;
}

enum keys {
    left = 0, right = 1, up = 2, down = 3,tab=4
};
const unsigned int COL = 10;
const unsigned int ROW = 10;
const int QUIT = 404;
const std::list<std::pair<int, int>> check_coordinates{std::make_pair(1, 0), std::make_pair(0, 1),
                                                       std::make_pair(-1, 0), std::make_pair(0, -1),
                                                       std::make_pair(1, 1), std::make_pair(-1, -1)};

constexpr bool is_in_board(const int &coordx, const int &coordy) {
    return coordx <= ROW - 1 && coordx >= 1 && coordy <= COL - 1 && coordy >= 1;
}

#endif //OTHELLO_HEADER_H
