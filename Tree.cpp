//
// Created by johann on 12/04/17.
//

#include "Tree.h"


void Tree::display_tree(const std::shared_ptr<Node> &node) {
    std::queue<std::shared_ptr<Node>> queue;
    std::vector<std::shared_ptr<Node>> next_nodes;
    int turn{0};
    int indentation{0};
    queue.push(base);
    while (!queue.empty()) {
        next_nodes = queue.front()->getNext();
        for (const auto &elem: next_nodes) {
            if (turn < elem->getSimulation().getNumber_of_turn()) {
                std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
                          << std::endl;
                ++turn;
            }
            indentation = 100 / (int) next_nodes.size();
            std::cout << std::setw(indentation) << ' ';
            std::cout << elem->getValue();
            queue.push(elem);
        }
        std::cout << "                                                                                  ";
        queue.pop();

    }
}


Tree::Tree(const std::shared_ptr<Node> &base, int depth, const Board &board, Ai &ai) :
        base(base), depth(depth) {
    update_tree(Tree::base, ai);
}

void Tree::update_tree(std::shared_ptr<Node> &node, Ai &ai) {
    Board current_map = node->getSimulation();
    bool is_opponent = node->getMin_max() == e_min_max::MIN;
    e_color color = (node->getMin_max() == e_min_max::MAX) ? ai.getColor() : opposite_color(ai.getColor());
    std::shared_ptr<Node> new_node;


    if (!node->isTerminal()) {
        for (const auto &elem : ai.list_choices(current_map, is_opponent)) {
            new_node = std::make_shared<Node>(Node(elem, node, color, getDepth()));
            node->add_next_node(new_node);
            update_tree(new_node, ai);
        }
    }
}

void Tree::min_max_value(std::shared_ptr<Node> &state) {
    std::vector<std::shared_ptr<Node>> next;
    std::vector<std::shared_ptr<Node>>::iterator min_max_score;
    if (state->getValue() != INFINITE) {
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

void Tree::min_max_algorithm() {
    while (getBase()->getValue() == INFINITE) {
        min_max_value(getBase());
    }
}
