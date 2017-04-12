//
// Created by johann on 11/04/17.
//

#include "Node.h"

void Node::add_next_node(const std::shared_ptr<Node> &to_add) {
next.push(to_add);
}

bool Node::operator<(const std::shared_ptr<Node> &rhs) const {
    if (getMin_max() == e_min_max::MAX) {
        return getValue() < rhs->getValue();
    } else { return getValue() > rhs->getValue(); }
}
