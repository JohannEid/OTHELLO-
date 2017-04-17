//
// Created by johann on 11/04/17.
//

#include "Node.h"

int Node::id = 0;


int Node::simulate_play(const e_color &color) {
    std::vector<std::pair<int, int>> flip_coordinates;
    flip_coordinates = simulation.get_encirclement(getAction_position().first,
                                                   getAction_position().second,
                                                   color);
    simulation.set_color(getAction_position().first, getAction_position().second, color);
    simulation.change_color(flip_coordinates, color);
    simulation.setNumber_of_turn(simulation.getNumber_of_turn() + 1);
    return (int) flip_coordinates.size();

}

int Node::value_fonction(const std::pair<int, int> &positon, Board &board_to_play, const e_color color) const {
    return (int) board_to_play.get_encirclement(positon.first, positon.second, color).size();
}

Node::Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> prec, e_color color,
           const int &depth) : action_position(action_position), prec(prec) {
    min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    simulation = prec->getSimulation();
    terminal = prec->getSimulation().getNumber_of_turn() == depth - 1;
    bool is_opponent{min_max == e_min_max::MAX};
    color = (is_opponent) ? opposite_color(color) : color;

    simulate_play(color);
    value = (terminal) ? value_fonction(action_position, simulation, color) : -1;


}

