//
// Created by johann on 29/03/17.
//

#include "Player.h"

void Player::play_turn(Board &board_to_play) {
    std::string icoordx{" "};
    std::string icoordy{" "};
    char coordx{' '};
    int coordy{0};


    std::cout << "Please choose a coordinate" << std::endl;
    while (true) {
        try {


            std::cin >> icoordx;
            std::cin >> icoordy;

            coordx = toupper(icoordx[0]);
            coordy = std::stoi(icoordy);

            if ((((int) coordx - 64 <= ROW - 2 && (int) coordx - 64 >= 1)
                 && (coordy <= COL - 2 && coordy >= 1))
                && (board_to_play.is_playable(coordx, coordy))) {
                board_to_play.set_color(coordx, coordy, getColor());
                break;
            } else {
                throw std::domain_error("Can't choose to perform this action");
            }


        }

        catch (std::exception const &e) {
            std::cerr << "Erreur" << e.what() << std::endl;
        }

    }

}
