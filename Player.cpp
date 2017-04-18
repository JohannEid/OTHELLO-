//
// Created by johann on 29/03/17.
//

#include "Player.h"
#include "Tree.h"


int Player::play_turn(Board &board_to_play, sf::RenderWindow &window) {
    std::cout << "called" << std::endl;
    std::vector<std::pair<int, int>> flip_coordinates;
    flip_coordinates = board_to_play.get_encirclement(board_to_play.getBase().first,
                                                      board_to_play.getBase().second,
                                                      getColor());
    board_to_play.set_color(board_to_play.getBase().first, board_to_play.getBase().second, getColor());
    board_to_play.change_color(flip_coordinates, getColor());
    return (int) flip_coordinates.size();
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

    for (int i{1}; i < ROW - 1; ++i) {
        for (int j{1}; j < COL - 1; ++j) {
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

int Player::moveSelection(sf::RenderWindow &window, Board &board) {
    show_targets(board);
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        int x{mouse_pos.x / square_size + 1};
        int y{mouse_pos.y / square_size + 1};
        if (board.getBoard(x, y).isTarget()) {
            board.setBase(std::make_pair(x, y));
            return 1;

        } else { return ERROR; }

    }
}


std::vector<std::pair<int, int>> Ai::list_choices(Board &board_to_play, bool is_opponent) const {
    std::vector<std::pair<int, int>> choices;
    e_color color = (is_opponent) ? opposite_color(getColor()) : getColor();
    for (int i{1}; i < ROW - 2; ++i) {
        for (int j{1}; j < COL - 2; ++j) {
            if (board_to_play.is_playable(i, j, color)) { choices.push_back(std::make_pair(i, j)); }
        }
    }
    return choices;
}


int Ai::play_turn(Board &board_to_play, sf::RenderWindow &window) {
    std::vector<std::pair<int, int>> flip_coordinates;
    choose_play(board_to_play);
    flip_coordinates = board_to_play.get_encirclement(board_to_play.getBase().first,
                                                      board_to_play.getBase().second,
                                                      getColor());
    board_to_play.set_color(board_to_play.getBase().first, board_to_play.getBase().second, getColor());
    board_to_play.change_color(flip_coordinates, getColor());
    return (int) flip_coordinates.size();
}


void Ai_easy::choose_play(Board &board_to_play) {

    std::vector<std::pair<int, int>> choices{list_choices(board_to_play)};
    int rand_index{rand() % (int) choices.size()};

    board_to_play.setBase(choices[rand_index]);

}

void Ai_medium::choose_play(Board &board_to_play) {
    board_to_play.setNumber_of_turn(0);
    Tree tree(std::make_shared<Node>(
            Node(std::make_pair(0, 0), e_min_max::MAX, -1, false, nullptr, board_to_play, getColor())),
              2, board_to_play, *this);
    tree.min_max_algorithm();
    std::cout << "the best value for this turn is : " << tree.getBase()->getValue() << std::endl;
    board_to_play.setBase(tree.getBase()->getMin_max_next()->getAction_position());
}

/*
Tree Ai_medium::create_tree(Board &board_to_play) {

    return tree;
}
*/

/*
void Ai_medium::min_max(Tree &tree) {
    while (tree.getBase()->getValue() == -1) {
        min_max_value(tree.getBase());
    }
}

void Ai_medium::min_max_value(std::shared_ptr<Node> &state) {
    std::vector<std::shared_ptr<Node>> next;
    std::vector<std::shared_ptr<Node>>::iterator min_max_score;
    if (state->getValue() != -1) {
        next = state->getPrec()->getNext();
        if (state->getPrec()->getMin_max() == e_min_max::MAX) {
            min_max_score = std::max_element(next.begin(), next.end(), Node::Order_node());
        } else { min_max_score = std::min_element(next.begin(), next.end(), Node::Order_node()); }
        state->getPrec()->setMin_max_next(next[std::distance(next.begin(), min_max_score)]);
    } else {
        for (auto elem: state->getNext()) {
            min_max_value(elem);
        }
    }
}
*/

