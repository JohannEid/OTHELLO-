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

Tree::Tree(const std::shared_ptr<Node> &base, int depth, Board &board, Ai &ai) :
        base(base), depth(depth) {
    update_tree(Tree::base, ai, board);
}

void Tree::update_tree(std::shared_ptr<Node> &node, Ai &ai, Board &board) {

    bool is_opponent = node->getMin_max() == e_min_max::MIN;
    e_color color = (node->getMin_max() == e_min_max::MAX) ? ai.getColor() : opposite_color(ai.getColor());
    e_color player_col = ai.getColor();
    std::shared_ptr<Node> new_node;
    Board_reverse board_reverse = node->simulate_play(player_col, board, getDepth());

    int value{board_reverse.value};

    if (node->isTerminal()) {
        reverse_action(board, board_reverse, player_col);
    }

    if (!node->isTerminal()) {
        for (const auto &elem : ai.list_choices(board, is_opponent)) {
            new_node = std::make_shared<Node>(Node(elem, node, value));
            node->add_next_node(new_node);
            reverse_action(board, board_reverse, player_col);
            update_tree(new_node, ai, board);
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

void Tree::reverse_action(Board &board, Board_reverse &board_reverse, const e_color &color) {
    board.change_color(board_reverse.switch_opponent_to_player, color);
    board.change_color(board_reverse.switch_player_to_opponent, opposite_color(color));
    board.change_color(board_reverse.color_to_none, e_color::NONE);
}

int Tree::alpha_beta_max(std::shared_ptr<Node>& node,int alpha, int beta) {
    if(node->isTerminal()){ return node->getValue();}
    for(auto& elem : node->next){
        node->setValue(alpha_beta_min(elem,alpha,beta));
        if(node->getValue() >=beta){return beta;}
        if(node->getValue()>alpha){alpha = node->getValue();}
    }
return alpha;
}

int Tree::alpha_beta_min(std::shared_ptr<Node>& node,int alpha, int beta) {
    if(node->isTerminal()){return node->getValue();}
    for(auto& elem : node->next){
        node->setValue(alpha_beta_max(elem,alpha,beta));
        if(node->getValue() <=alpha){return alpha;}
        if(node->getValue()<beta){beta = node->getValue();}

    }
    return beta;
}

void Tree::alpha_beta_search() {
    alpha_beta_max(base,-INFINITE,INFINITE);
}


