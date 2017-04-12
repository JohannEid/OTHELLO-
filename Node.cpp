//
// Created by johann on 11/04/17.
//

#include "Node.h"


bool Node::operator<(const std::shared_ptr<Node> &rhs) const {
    if (getMin_max() == e_min_max::MAX) {
        return getValue() < rhs->getValue();
    } else { return getValue() > rhs->getValue(); }
}

int Node::simulate_play(const e_color& color) {
    std::vector<std::pair<int, int>> flip_coordinates;
    flip_coordinates = simulation.get_encirclement(simulation.getBase().first,
                                                   simulation.getBase().second,
                                                      color);
    simulation.set_color(simulation.getBase().first, simulation.getBase().second, color);
    simulation.change_color(flip_coordinates, color);
    return flip_coordinates.size();

}
