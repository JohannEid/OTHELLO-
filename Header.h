//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_HEADER_H
#define OTHELLO_HEADER_H

#include "bits/stdtr1c++.h"
#include "rlutil.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <fstream>
#include <queue>
#include <assert.h>
#include <iomanip>
#include <limits>


const int window_width = 960;
const int window_height = 928;
const int square_size = 84;
const int ERROR = 1008;
const int INFINITE = std::numeric_limits<int>::max();


enum class e_color {
    WHITE, BLACK, NONE
};


enum class e_min_max {
    MIN, MAX
};

inline void clearconsole() {
    for (int i{0}; i < 20; ++i)
        std::cout << std::endl;
}

enum keys {
    left = 0, right = 1, up = 2, down = 3, tab = 4
};
const unsigned int COL = 10;
const unsigned int ROW = 10;
const int QUIT = 404;
const std::list<std::pair<int, int>> check_coordinates{std::make_pair(1, 0), std::make_pair(0, 1),
                                                       std::make_pair(-1, 0), std::make_pair(0, -1),
                                                       std::make_pair(1, 1), std::make_pair(-1, -1),
                                                       std::make_pair(1, -1), std::make_pair(-1, 1)};

const std::list<std::pair<int, int>> key_stability_positions{
        std::make_pair(1, 1), std::make_pair(1, 2), std::make_pair(2, 1),
        std::make_pair(1, 8), std::make_pair(2, 8), std::make_pair(1, 7),
        std::make_pair(8, 1), std::make_pair(8, 2), std::make_pair(7, 1),
        std::make_pair(8, 8), std::make_pair(8, 7), std::make_pair(7, 8),
};

constexpr bool is_in_board(const int &coordx, const int &coordy) {
    return coordx <= ROW - 2 && coordx >= 1 && coordy <= COL - 2 && coordy >= 1;
}


constexpr e_color opposite_color(const e_color &color) {
    return (color == e_color::WHITE) ? e_color::BLACK : e_color::WHITE;
}

inline bool is_found(const std::vector<std::pair<int, int>> vector, const std::pair<int, int> item) {
    return (std::find(vector.begin(), vector.end(), item) != vector.end());
}
struct Texture_manager {
    sf::Texture texture[5];

    void load_texture() {
        assert(texture[0].loadFromFile("sprites/chinese_flag.png"));
        assert(texture[1].loadFromFile("sprites/usa_flag.png"));
        assert(texture[2].loadFromFile("sprites/target.png"));
        assert(texture[3].loadFromFile("sprites/menu_v5.png"));
        assert(texture[4].loadFromFile("sprites/board_v3.png"));

    }

};


const int HvHxl = 350;
const int HvHxr = 635;
const int HvHyl = 458;
const int HvHyr = 477;

const int AIexl = 351;
const int AIexr = 649;
const int AIeyl = 544;
const int AIeyr = 566;

const int AImxl = 323;
const int AImxr = 665;
const int AImyl = 635;
const int AImyr = 652;


const int AIhxl = 272;
const int AIhxr = 714;
const int AIhyl = 811;
const int AIhyr = 827;

const int SAVExl = 340;
const int SAVExr = 642;
const int SAVEyl = 723;
const int SAVEyr = 732;


const int SHIFTX = 120;
const int SHIFY = 110;

#endif //OTHELLO_HEADER_H
