//
// Created by johann on 29/03/17.
//

#include "Player.h"

int Player::play_turn(Board &board_to_play) {
    std::string icoordx{" "};
    std::string icoordy{" "};
    char coordx{' '};
    int coordy{0};
    int number_of_color_change{0};


    std::cout << "Please choose a coordinate" << std::endl;
    while (true) {
        try {

            std::cin >> icoordx;
            std::cin >> icoordy;

            coordx = (int) toupper(icoordx[0]) - 64;
            coordy = std::stoi(icoordy);

            if ((((coordx <= ROW - 2) && coordx >= 1)
                 && (coordy <= COL - 2 && coordy >= 1))
                && (board_to_play.is_playable(coordx, coordy, getColor()))) {
                board_to_play.set_color(coordx, coordy, getColor());
                number_of_color_change = board_to_play.change_color(coordx, coordy, getColor());
                break;
            } else {
                throw std::domain_error("Can't choose to perform this action");
            }
        }
        catch (std::exception const &e) {
            std::cerr << "Error" << e.what() << std::endl;
        }

    }
    return number_of_color_change;
}

bool Player::is_allowed(const Board &board) const {
    for (int i{1}; i < ROW - 2; ++i) {
        for (int j{1}; j < COL - 2; ++j) {
            if (board.is_playable(i, j, getColor())) { return true; }
        }
    }
    return false;
}
