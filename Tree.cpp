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
                std::cout << std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
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
