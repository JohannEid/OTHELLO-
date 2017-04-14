//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_HEADER_H
#define OTHELLO_HEADER_H

#include "bits/stdtr1c++.h"
#include "rlutil.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <fstream>


enum class e_color {
    WHITE, BLACK, NONE
};


enum class e_min_max {
    MIN, MAX
};

inline void clearconsole() {
    for (int i{0}; i < 20; ++i)
        std::cout << std::endl; }

enum keys {
    left = 0, right = 1, up = 2, down = 3, tab = 4
};
const unsigned int COL = 10;
const unsigned int ROW = 10;
const int QUIT = 404;
const std::list<std::pair<int, int>> check_coordinates{std::make_pair(1, 0), std::make_pair(0, 1),
                                                       std::make_pair(-1, 0), std::make_pair(0, -1),
                                                       std::make_pair(1, 1), std::make_pair(-1, -1)};

constexpr bool is_in_board(const int &coordx, const int &coordy) {
    return coordx <= ROW - 2 && coordx >= 1 && coordy <= COL - 2 && coordy >= 1;
}


constexpr e_color opposite_color(const e_color &color) {
    return (color == e_color::WHITE) ? e_color::BLACK : e_color::WHITE;
}

constexpr e_color min_max_color(const e_min_max &min_max,  e_color color) {
    return (min_max == e_min_max::MAX)? color:opposite_color(color);
}


#endif //OTHELLO_HEADER_H
