//
// Created by johann on 11/04/17.
//

#include "Node.h"

#include "Node.h"


Board_reverse Node::simulate_play(e_color &color, Board &board, const int &depth) {
    Board_reverse board_reverse;
    std::vector<std::pair<int, int>> flip_coordinates;
    e_color new_color = color;
    int player_score{0};
    int opponent_score{0};
    bool terminal = getLast_moves().size() == depth - 1;
    for (int i{0}; i < getLast_moves().size(); ++i) {

        new_color = (i % 2 == 0) ? color : opposite_color(color);
        flip_coordinates = board.get_encirclement(getLast_moves()[i].first,
                                                  getLast_moves()[i].second,
                                                  new_color);
        board.set_color(getLast_moves()[i].first, getLast_moves()[i].second, new_color);
        board.change_color(flip_coordinates, new_color);
        board_reverse.color_to_none.push_back(getLast_moves()[i]);
        if (new_color == opposite_color(color)) {
            board_reverse.switch_opponent_to_player.insert(board_reverse.switch_opponent_to_player.end(),
                                                           flip_coordinates.begin(),
                                                           flip_coordinates.end());

        } else if (new_color == color) {
            board_reverse.switch_player_to_opponent.insert(board_reverse.switch_player_to_opponent.end(),
                                                           flip_coordinates.begin(),
                                                           flip_coordinates.end());
        }
        board.setNumber_of_turn(simulation.getNumber_of_turn() + 1);

    }
    board_reverse.value = (terminal)?heuristic_value(board_reverse,board):INFINITE;
    return board_reverse;
}



Node::Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> prec,
           const int &value) : value(value), prec(prec), action_position(action_position) {
    terminal = (value != INFINITE);
    min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    last_moves = prec->getLast_moves();
    add_moves(action_position);
}

int Node::heuristic_value(Board_reverse &board_reverse, Board &board) {
    int coin_parity{0};
    int mobility_value{0};
    int corners_captured{0};
    std::pair<int, int> corner = list_corner(board, e_color::BLACK);

    int max_score{(int) board_reverse.switch_player_to_opponent.size() + (int) board_reverse.color_to_none.size() / 2 +
                  (int) board_reverse.color_to_none.size() % 2};
    int min_score{(int) board_reverse.switch_opponent_to_player.size() + (int) board_reverse.color_to_none.size() / 2};
    int max_mobility{list_mobility(board, e_color::BLACK)};
    int min_mobility{list_mobility(board, e_color::WHITE)};
    int max_corner{corner.first};
    int min_corner{corner.second};


    coin_parity = 100 * (max_score - min_score) / (max_score + min_score);
    mobility_value = (max_mobility + min_mobility != 0) ? 100 * (max_mobility - min_mobility) /
                                                          (max_mobility + min_mobility) : 0;
    corners_captured = (max_corner + min_corner != 0) ? 100 * (max_corner - min_corner) / (max_corner + min_corner) : 0;

    return coin_parity + mobility_value + corners_captured;


}

int Node::list_mobility(const Board &board_to_play, const e_color &color) const {
    int mobility{0};
    for (int i{1}; i < ROW - 1; ++i) {
        for (int j{1}; j < COL - 1; ++j) {
            if (board_to_play.is_playable(i, j, color)) { ++mobility; }
        }
    }
    return mobility;
}

std::pair<int, int> Node::list_corner(const Board &board_to_play, const e_color &color) {
    int max_corner_number{0};
    int min_corner_number{0};
    std::vector<std::pair<int, int>> corners{std::make_pair(1, 1), std::make_pair(1, 8),
                                             std::make_pair(8, 1), std::make_pair(8, 8)};
    for (const auto &elem : corners) {
        if (board_to_play.getBoard(elem.first, elem.second).getColor() == color) { ++max_corner_number; }
        else if (board_to_play.getBoard(elem.first, elem.second).getColor() ==
                 opposite_color(color)) { ++min_corner_number; }
    }
    return std::make_pair(max_corner_number, min_corner_number);
}



