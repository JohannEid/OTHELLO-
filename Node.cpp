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
    int flip_number{0};
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
    player_score = (int) board_reverse.switch_player_to_opponent.size();
    opponent_score = (int) board_reverse.switch_opponent_to_player.size();


    board_reverse.value = value_fonction(getLast_moves(), getSimulation(), color, player_score - opponent_score, depth);
    return board_reverse;
}

int
Node::value_fonction(const std::vector<std::pair<int, int>> &positon, const Board &board_to_play, const e_color color,
                     int flip_number, const int &depth) {
    bool terminal = positon.size() == depth - 1;
    return (terminal == true ) ? flip_number : INFINITE;
}


Node::Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> prec,
           const int &value) : value(value), prec(prec), action_position(action_position) {
    terminal = (value != INFINITE);
    min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    last_moves = prec->getLast_moves();
    add_moves(action_position);
}

