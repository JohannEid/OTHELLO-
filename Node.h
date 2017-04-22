//
// Created by johann on 11/04/17.
//

#ifndef OTHELLO_NODE_H
#define OTHELLO_NODE_H

#include "Header.h"
#include "Board.h"

struct Board_reverse {
    std::vector<std::pair<int, int>> color_to_none;
    std::vector<std::pair<int, int>> mitoma;
    std::vector<std::pair<int, int>> matomi;
    int value;
    int max_score;
    int min_score;
};


class Node {
private:
    std::pair<int, int> action_position;
    e_min_max min_max;
    int value;
    bool terminal;
    std::shared_ptr<Node> prec;
    std::vector<std::pair<int, int>> last_moves;
public:

    std::vector<std::shared_ptr<Node>> next;

    Node(const std::pair<int, int> &action_position, e_min_max min_max, int value, bool terminal,
         const std::shared_ptr<Node> &prec, const Board &board, const e_color &color) : action_position(
            action_position), min_max(min_max), value(value),
                                                                                        terminal(terminal), prec(prec)
                                                                                        {}

    Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node>& prec,
         const int &value);


    struct Order_node {
        bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
            return lhs->value < rhs->value;
        }
    };

    int heuristic_value(Board_reverse &board_reverse, Board &board);

    const std::pair<int, int> &getAction_position() const {
        return action_position;
    }

    void add_next_node(const std::shared_ptr<Node> &to_add) {
        next.push_back(to_add);
    }

    const std::vector<std::shared_ptr<Node>> &getNext() const {
        return next;
    }

    Board_reverse simulate_play(e_color &color, Board &board, const int &depth);

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

    void setValue(int value) {
        Node::value = value;
    }

    void add_moves(const std::pair<int, int> &move) {
        last_moves.push_back(move);
    }

    const std::vector<std::pair<int, int>> &getLast_moves() const {
        return last_moves;
    }

    int list_mobility(const Board &board_to_play, const e_color &color) const;

    std::pair<int, int> list_corner(const Board &board_to_play, const e_color &color);

    std::pair<int,int> evaluate_stability(const Board& board_to_play);


};


#endif //OTHELLO_NODE_H
