//
// Created by johann on 29/03/17.
//

#include "Player.h"

int Player::play_turn(Board &board_to_play) {
    std::string icoordx{" "};
    std::string icoordy{" "};
    char coordx{' '};
    int iocoordx;
    int coordy{0};
    int flip_number{0};
    std::vector<std::pair<int,int>> flip_coordinates;


    std::cout << "Please choose a coordinate" << std::endl;
    while (true) {
        try {

            std::cin >> icoordx;
            std::cin >> icoordy;

            coordx = (int) toupper(icoordx[0]) - 64;
            coordy = std::stoi(icoordy);
            iocoordx = coordx;

            if ((((coordx <= ROW - 2) && coordx >= 1)
                 && (coordy <= COL - 2 && coordy >= 1))
                && (board_to_play.is_playable(iocoordx, coordy, getColor()))) {
                flip_coordinates = board_to_play.get_encirclement(iocoordx,coordy,getColor());
                board_to_play.set_color(coordx, coordy, getColor());
                board_to_play.change_color(flip_coordinates,getColor());
                flip_number = flip_coordinates.size();
                break;
            } else {
                throw std::domain_error("Can't choose to perform this action");
            }
        }
        catch (std::exception const &e) {
            std::cerr << "Error" << e.what() << std::endl;
        }

    }
    return flip_number;
}

bool Player::is_allowed(const Board &board) const {
    for (int i{1}; i < ROW - 2; ++i) {
        for (int j{1}; j < COL - 2; ++j) {
            if (!board.get_encirclement(i,j,getColor()).empty()) { return true; }
        }
    }
    return false;
}
