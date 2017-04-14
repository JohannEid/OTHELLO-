//
// Created by johann on 12/04/17.
//

#include "Tree.h"

/*
void Tree::display_tree() {
    std::queue<std::shared_ptr<Node>> queue;
    int indentation{0};
    queue.push(base);
    while (!queue.empty()) {
        std::cout <<queue.front()->getNext().size()<<std::endl;
        for (const auto &elem: queue.front()->getNext()) {
            indentation = 20 / (int) queue.front()->getNext().size();
            std::cout << std::setw(indentation) << ' ';
            std::cout <<elem->getId_n();
            queue.push(elem);
        }
        std::cout << std::endl;
        queue.pop();
    }
}
*/