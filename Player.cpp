//
// Created by johann on 29/03/17.
//

#include "Player.h"

int Player::play_turn(Board &board_to_play) {
    int base_position_x{0};
    int base_position_y{0};

    std::string icoordx{" "};
    std::string icoordy{" "};
    char coordx{' '};
    int iocoordx;
    int coordy{0};
    int flip_number{0};
    std::vector<std::pair<int, int>> flip_coordinates;

    show_targets(board_to_play);
    board_to_play.display(getColor());


    std::cout << "Please choose a coordinate" << std::endl;
    while (true) {
        try {

            std::cin >> icoordx;
            std::cin >> icoordy;

            coordx = (int) toupper(icoordx[0]) - 64;
            coordy = std::stoi(icoordy);

            if (is_in_board(coordx, coordy)
                && (board_to_play.is_playable(coordx, coordy, getColor()))) {
                board_to_play.set_color(coordx, coordy, getColor());
                flip_coordinates = board_to_play.get_encirclement(coordx, coordy, getColor());
                board_to_play.change_color(flip_coordinates, getColor());
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
            if (board.is_playable(i, j, getColor())) { return true; }
        }
    }
    return false;
}


void Player::show_targets(Board &board_to_play) const {

    for (int i{1}; i < ROW - 2; ++i) {
        for (int j{1}; j < COL - 2; ++j) {
            if (board_to_play.is_playable(i, j, getColor())) { board_to_play.setTarget(i, j, true); }
            else { board_to_play.setTarget(i, j, false); }
        }
    }

}

void Player::player_mvt(Board &board, const int &base_pos_x, const int &base_pos_y) {
    sf::Event event;

    while (event.key.code != sf::Keyboard::Return) {
        switch (event.key.code) {
            case sf::Keyboard::Q:
                handle_mvt(board, std::make_pair(-1, 0));
                break;

            case sf::Keyboard::Z:
                handle_mvt(board, std::make_pair(0, -1));
                break;

            case sf::Keyboard::D:
                handle_mvt(board, std::make_pair(1, 0));
                break;

            case sf::Keyboard::S:
                handle_mvt(board, std::make_pair(0, 1));
                break;
        }
    }

}

void Player::handle_mvt(Board &board, const std::pair<int, int> &move_coord) {
    std::pair<int, int> new_position{std::make_pair(board.getBase().first + move_coord.first,
                                                    board.getBase().second + move_coord.second)};
    if (is_in_board(board.getBase().first + move_coord.first,
                    board.getBase().second + move_coord.second)) {
        board.setBase(new_position);
    } else {
        std::cout << "can't change position" << std::endl;
    }

}
