//
// Created by johann on 11/04/17.
//

#include "Node.h"

bool Node::operator<(const Node &to_compare) {
    if (getMin_max() == e_min_max::MIN) {
        return getValue() < to_compare.getValue();
    } else { return getValue() > to_compare.getValue(); }
}
