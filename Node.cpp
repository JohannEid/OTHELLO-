//
// Created by johann on 11/04/17.
//

#include "Node.h"


/*
int Node::id = 0;


int Node::simulate_play(const e_color &color) {
    std::vector<std::pair<int, int>> flip_coordinates;
    flip_coordinates = simulation.get_encirclement(getAction_position().first,
                                                   getAction_position().second,
                                                   color);
    simulation.set_color(getAction_position().first, getAction_position().second, color);
    simulation.change_color(flip_coordinates, color);
    simulation.setNumber_of_turn(simulation.getNumber_of_turn() + 1);
    value_fonction(action_position, getSimulation(), color, (int) flip_coordinates.size());
    return 404;
}

int Node::value_fonction(const std::pair<int, int> &positon, const Board &board_to_play, const e_color color,
                         int flip_number) {
    value = (terminal) ? flip_number : INFINITE;
}


Node::Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> prec, e_color color,
           const int &depth) : action_position(action_position), prec(prec) {
    min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    simulation = prec->getSimulation();
    bool is_opponent = min_max == e_min_max::MAX;
    terminal = simulation.getNumber_of_turn() == depth - 1;
    simulate_play(color);
    value = (is_opponent) ? -value : value;

}
 */


#include "Node.h"

int Node::id = 0;


Board_reverse Node::simulate_play(e_color &color, Board &board, const int &depth) {
    Board_reverse board_reverse;
    std::vector<std::pair<int, int>> flip_coordinates;
    e_color new_color = color;

    for (int i{0}; i < getLast_moves().size(); ++i) {

        new_color = (i % 2 == 0) ? color : opposite_color(color);
        flip_coordinates = board.get_encirclement(getLast_moves()[i].first,
                                                  getLast_moves()[i].second,
                                                  new_color);
        board.set_color(getLast_moves()[i].first, getLast_moves()[i].second, new_color);
        board.change_color(flip_coordinates, new_color);
        board_reverse.color_to_none.push_back(getLast_moves()[i]);
        if (new_color == opposite_color(color)) {
            board_reverse.switch_opponent_to_player.insert(board_reverse.switch_opponent_to_player.end(), flip_coordinates.begin(),
                                                    flip_coordinates.end());

        }
        else if (new_color == color) {
            board_reverse.switch_player_to_opponent.insert(board_reverse.switch_player_to_opponent.end(), flip_coordinates.begin(),
                                                    flip_coordinates.end());
        }
        board.setNumber_of_turn(simulation.getNumber_of_turn() + 1);

    }
    board.display_(color, 5);
    board_reverse.value = value_fonction(getLast_moves(), getSimulation(), color, (int) flip_coordinates.size(), depth);

    return board_reverse;
}

int
Node::value_fonction(const std::vector<std::pair<int, int>> &positon, const Board &board_to_play, const e_color color,
                     int flip_number, const int &depth) {
    bool terminal = positon.size() == depth;
    return (terminal) ? flip_number : INFINITE;
}

/*
Node::Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> prec, e_color color,
           const int &depth) : action_position(action_position), prec(prec) {

    min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    simulation = prec->getSimulation();
    bool is_opponent = min_max == e_min_max::MAX;
    terminal = simulation.getNumber_of_turn() == depth - 1;
    //simulate_play(color);
    value = (is_opponent) ? -value : value;
    std::cout <<"Number of turns:"<<simulation.getNumber_of_turn()<<std::endl;
    std::cout << "Value:" << value << std::endl;

    last_moves = prec->getLast_moves();
    add_moves(action_position);

    terminal = last_moves.size() == depth;

}
*/
Node::Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> prec,
           const int &value) : value(value) {
    terminal = (value != INFINITE);
    min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    last_moves = prec->getLast_moves();
    add_moves(action_position);
}

