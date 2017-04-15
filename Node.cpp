//
// Created by johann on 11/04/17.
//

#include "Node.h"
int Node ::id = 0;


int Node::simulate_play(const e_color& color) {
    std::vector<std::pair<int, int>> flip_coordinates;
    flip_coordinates = simulation.get_encirclement(getAction_position().first,
                                                   getAction_position().second,
                                                      color);
    simulation.set_color(getAction_position().first, getAction_position().second, color);
    simulation.change_color(flip_coordinates, color);
    simulation.setNumber_of_turn(simulation.getNumber_of_turn()+1);
    return (int) flip_coordinates.size();

}

