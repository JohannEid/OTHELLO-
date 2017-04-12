//
// Created by johann on 12/04/17.
//

#ifndef OTHELLO_TREE_H
#define OTHELLO_TREE_H

#include "Node.h"

class Tree {
private:
    std::shared_ptr<Node> base;
    std::shared_ptr<Node> current = base;


    int depth{0};


public:
    Tree(const std::shared_ptr<Node> &base, int depth) : base(base), depth(depth) {}



    const std::shared_ptr<Node> &getBase() const {
        return base;
    }

    int getDepth() const {
        return depth;
    }

    void setBase(const std::shared_ptr<Node> &base) {
        Tree::base = base;
    }

    void setDepth(int depth) {
        Tree::depth = depth;
    }
    const std::shared_ptr<Node> &getCurrent() const {
        return current;
    }

    void setCurrent(const std::shared_ptr<Node> &current) {
        Tree::current = current;
    }

};


#endif //OTHELLO_TREE_H
