//
// Created by johann on 12/04/17.
//

#ifndef OTHELLO_TREE_H
#define OTHELLO_TREE_H

#include "Node.h"
#include "Player.h"

class Tree {
private:
    std::shared_ptr<Node> base;
    std::shared_ptr<Node> current = base;
    int number_turn = 0; //for diplay function
    int depth{0};


public:
    Tree(const std::shared_ptr<Node> &base, int depth, Board &board,
         Ai &player);

    void update_tree(std::shared_ptr<Node> &node, Ai &ai, Board &board);

    void min_max_algorithm();

    int min_max_min(std::shared_ptr<Node> &node);

    int min_max_max(std::shared_ptr<Node> &node);

    //void min_max_value(std::shared_ptr<Node> &state);

    int negaMax(std::shared_ptr<Node>& node );

    void alpha_beta_search();

    void negaMax_algorithm();

    int alpha_beta_max(std::shared_ptr<Node> &node, int alpha, int beta);

    int alpha_beta_min(std::shared_ptr<Node> &node, int alpha, int beta);

    void reverse_action(Board &board, Board_reverse &board_reverse, const e_color &color);


    std::shared_ptr<Node> &getBase() {
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


    void display_tree(const std::shared_ptr<Node> &node);
};


#endif //OTHELLO_TREE_H
