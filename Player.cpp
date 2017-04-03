//
// Created by johann on 29/03/17.
//

#include "Player.h"


int Player::play_turn(Board &board_to_play) {
    std::vector<std::pair<int, int>> flip_coordinates;
    show_targets(board_to_play);
    player_mvt(board_to_play);
    flip_coordinates = board_to_play.get_encirclement(board_to_play.getBase().first,
                                                      board_to_play.getBase().second,
                                                      getColor());
    board_to_play.change_color(flip_coordinates, getColor());


    /*
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
     */
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

void Player::player_mvt(Board &board) {
    std::vector<bool> key_states{false, false, false, false};
    while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && board.getBoard(board.getBase().first,
                                                                                board.getBase().second).isTarget())) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            update_key_state(board, key_states, left);
        } else { key_states[left] = false; }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            update_key_state(board, key_states, right);
        } else { key_states[right] = false; }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            update_key_state(board, key_states, up);
        } else { key_states[up] = false; }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            update_key_state(board, key_states, down);
        } else { key_states[down] = false; }
    }
}


void Player::handle_mvt(Board &board, const std::vector<bool> &key_states) {
    std::pair<int, int> move_coord{handle_key_states(key_states)};
    std::pair<int, int> new_position{std::make_pair(board.getBase().first + move_coord.first,
                                                    board.getBase().second + move_coord.second)};

    if (is_in_board(new_position.first, new_position.second)) {
        board.setBase(new_position);
    } else {
        std::cout << "Can't change position" << std::endl;
    }
    board.display(getColor());

}


std::pair<int, int> Player::handle_key_states(const std::vector<bool> &key_states) {
    if (key_states[left]) { return std::make_pair(0, -1); }
    else if (key_states[right]) { return std::make_pair(0, 1); }
    else if (key_states[up]) { return std::make_pair(-1, 0); }
    else if (key_states[down]) { return std::make_pair(1, 0); }
}

void Player::update_key_state(Board &board, std::vector<bool> &key_states, const keys &key) {
    if (!key_states[key]) {
        key_states[key] = true;
        handle_mvt(board, key_states);
    }

}
