//
// Created by johann on 29/03/17.
//

#include "Player.h"
#include "Tree.h"


int Player::play_turn(Board &board_to_play, sf::RenderWindow &window) {
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


void Player::display_player_score(const Board &board) const {
    int opponent_score{board.getNumber_of_turn() + 4 - getScore()};
    std::cout << "Player score is :" << getScore() << std::endl;
    std::cout << "Opponent score is :" << opponent_score << std::endl;
    std::cout << "Number of turn is : " << board.getNumber_of_turn() << std::endl;
    std::cin.ignore(256, '\n');
}

int Player::moveSelection(sf::RenderWindow &window, Board &board) {
    show_targets(board);

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int x{(mouse_pos.x - SHIFTX) / square_size +1} ;
    int y{(mouse_pos.y - SHIFY) / square_size  +1};

    if (board.getBoard(x, y).isTarget()) {
        board.setBase(std::make_pair(x, y));
        return 1;

    } else { return ERROR; }


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
            Node(std::make_pair(0, 0), e_min_max::MAX, INFINITE, false, nullptr, board_to_play, getColor())),
              3, board_to_play, *this);
    tree.min_max_algorithm();
    std::cout << "the best value for this turn is : " << tree.getBase()->getValue() << std::endl;
    std::cout <<"x:"<<tree.getBase()->getMin_max_next()->getAction_position().first<<std::endl;
    std::cout <<"y:"<<tree.getBase()->getMin_max_next()->getAction_position().second<<std::endl;

    board_to_play.setBase(tree.getBase()->getMin_max_next()->getAction_position());
}



