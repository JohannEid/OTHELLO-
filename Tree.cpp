//
// Created by johann on 12/04/17.
//

#include "Tree.h"


void Tree::display_tree() {
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
            std::cout << elem->getId_n();
            queue.push(elem);
        }
        queue.pop();
    }
}

Tree::Tree(const std::shared_ptr<Node> &base, int depth, const Board &board, Ai &ai) :
        base(base), depth(depth) {

    Board simulation = board;
    std::queue<std::shared_ptr<Node>> queue;
    queue.push(getCurrent());
    while (!queue.empty()) {
        if (queue.front()->isTerminal()) { break; }
        else { setCurrent(queue.front()); }
        update_tree(queue, ai);
    }

}

void Tree::update_tree(std::queue<std::shared_ptr<Node>> &queue, Ai &ai) {
    std::shared_ptr<Node> prec = getCurrent();
    std::shared_ptr<Node> new_node;
    e_min_max min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    int value{0};
    Board current_map = getCurrent()->getSimulation();
    bool terminal{prec->getSimulation().getNumber_of_turn() == getDepth() - 1};
    bool is_opponent{min_max == e_min_max::MAX};
    e_color color = (is_opponent) ? opposite_color(ai.getColor()) : ai.getColor();
    std::vector<std::pair<int, int>> possible = ai.list_choices(current_map, is_opponent);


    for (const auto &elem: possible) {
        value = (terminal) ? ai.value_fonction(elem, current_map, color) : -1;
        new_node = std::make_shared<Node>(Node(elem, min_max, value, terminal, prec, current_map, color));
        getCurrent()->add_next_node(new_node);
        queue.push(new_node);
        std::cout << "the size of queue is" << queue.size() << std::endl;
        std::cout << "Building tree ...." << std::endl;
        std::cout << elem.first << elem.second << std::endl;
        if (terminal) { std::cout << "this is terminal" << std::endl; }

    }
    queue.pop();
}

void Tree::min_max_value(std::shared_ptr<Node>& state) {
    std::vector<std::shared_ptr<Node>> next;
    std::vector<std::shared_ptr<Node>>::iterator min_max_score;
    if (state->getValue() != -1) {
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
    while (getBase()->getValue() == -1) {
        min_max_value(getBase());
    }
}
