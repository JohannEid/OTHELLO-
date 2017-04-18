//
// Created by johann on 11/04/17.
//

#ifndef OTHELLO_NODE_H
#define OTHELLO_NODE_H

#include "Header.h"
#include "Board.h"


class Node {
private:
    std::pair<int, int> action_position;
    Board simulation;
    e_min_max min_max;
    int value, id_n;
    static int id;
    bool terminal;
    std::shared_ptr<Node> prec, min_max_next;
    std::vector<std::shared_ptr<Node>> next;
public:


    Node(const std::pair<int, int> &action_position, e_min_max min_max, int value, bool terminal,
         const std::shared_ptr<Node> &prec, const Board &board, const e_color &color) : action_position(
            action_position), min_max(min_max), value(value),
                                                                                        terminal(terminal), prec(prec),
                                                                                        simulation(board),
                                                                                        id_n(Node::id++) {
        if (action_position != std::make_pair(0, 0))simulate_play(color);
    }

    Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> prec,  e_color color,
         const int& depth);


    struct Order_node {
        bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
            return lhs->value < rhs->value;
        }
    };

    int value_fonction(const std::pair<int, int> &positon,const Board &board_to_play, const e_color color, int flip_number) ;

    const std::pair<int, int> &getAction_position() const {
        return action_position;
    }

    void add_next_node(const std::shared_ptr<Node> &to_add) {
        next.push_back(to_add);
    }

    const std::vector<std::shared_ptr<Node>> &getNext() const {
        return next;
    }

    const Board &getSimulation() const {
        return simulation;
    }

    int simulate_play(const e_color &color);

    e_min_max getMin_max() const {
        return min_max;
    }

    int getValue() const {
        return value;
    }

    bool isTerminal() const {
        return terminal;
    }

    const std::shared_ptr<Node> &getPrec() const {
        return prec;
    }

    int getId_n() const {
        return id_n;
    }

    void setValue(int value) {
        Node::value = value;
    }

    const std::shared_ptr<Node> &getMin_max_next() const {
        return min_max_next;
    }

    void setMin_max_next(const std::shared_ptr<Node> &min_max_next) {
        Node::min_max_next = min_max_next;
        setValue(min_max_next->getValue());
    }

};


#endif //OTHELLO_NODE_H
