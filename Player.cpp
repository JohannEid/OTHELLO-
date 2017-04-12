//
// Created by johann on 29/03/17.
//

#include "Player.h"


int Player::play_turn(Board &board_to_play) {
    std::vector<std::pair<int, int>> flip_coordinates;
    show_targets(board_to_play);
    if (!player_input(board_to_play)) { return 404; };
    flip_coordinates = board_to_play.get_encirclement(board_to_play.getBase().first,
                                                      board_to_play.getBase().second,
                                                      getColor());
    board_to_play.set_color(board_to_play.getBase().first, board_to_play.getBase().second, getColor());
    board_to_play.change_color(flip_coordinates, getColor());
    return flip_coordinates.size();
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

bool Player::player_input(Board &board) {
    std::vector<bool> key_states{false, false, false, false, false};
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            update_key_state(board, key_states, tab);
        } else { key_states[tab] = false; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return false;
        }
    }
    return true;
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
    if (!key_states[key] && key != tab) {
        key_states[key] = true;
        handle_mvt(board, key_states);
    } else if (key == tab) {
        display_player_score(board);
    }

}

void Player::display_player_score(const Board &board) const {
    int opponent_score{board.getNumber_of_turn() + 4 - getScore()};
    std::cout << "Player score is :" << getScore() << std::endl;
    std::cout << "Opponent score is :" << opponent_score << std::endl;
    std::cout << "Number of turn is : " << board.getNumber_of_turn() << std::endl;
    std::cin.ignore(256, '\n');
}


int Ai_easy::play_turn(Board &board_to_play) {
    std::vector<std::pair<int, int>> flip_coordinates;
    choose_play(board_to_play);
    flip_coordinates = board_to_play.get_encirclement(board_to_play.getBase().first,
                                                      board_to_play.getBase().second,
                                                      getColor());
    board_to_play.set_color(board_to_play.getBase().first, board_to_play.getBase().second, getColor());
    board_to_play.change_color(flip_coordinates, getColor());
    return (int) flip_coordinates.size();

}

std::vector<std::pair<int, int>> Ai::list_choices(Board &board_to_play) const {
    std::vector<std::pair<int, int>> choices;
    for (int i{1}; i < ROW - 2; ++i) {
        for (int j{1}; j < COL - 2; ++j) {
            if (board_to_play.is_playable(i, j, getColor())) { choices.push_back(std::make_pair(i, j)); }
        }
    }
    return choices;
}

int Ai::value_fonction(const std::pair<int, int> &positon, Board &board_to_play) const {
    return (int) board_to_play.get_encirclement(positon.first, positon.second, getColor()).size();
}

void Ai_easy::choose_play(Board &board_to_play) {
    std::vector<std::pair<int, int>> choices{list_choices(board_to_play)};
    int rand_index{rand() % (int) choices.size()};

    board_to_play.setBase(choices[rand_index]);

}

void Ai_medium::choose_play(Board &board_to_play) {
    min_max(board_to_play);

}

void Ai_medium::min_max(Board &board_to_play) const {
    create_tree(board_to_play);

}

void Ai_medium::create_tree(Board &board_to_play) const {
    Board simulation = board_to_play;
    Node base(std::make_pair(0, 0), e_min_max::MAX, 0, false, nullptr);
    for (const auto &elem: list_choices(simulation)) {
        std::cout << elem.first;
    }

}

int Ai_medium::play_turn(Board &board_to_play) {
    choose_play(board_to_play);
}
