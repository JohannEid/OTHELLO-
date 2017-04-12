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
    e_min_max min_max;
    int value;
    bool terminal;
    std::shared_ptr<Node> prec;
    std::vector<std::shared_ptr<Node>> next;
    Board simulation;
    bool visited;
public:


    Node(const std::pair<int, int> &action_position, e_min_max min_max, int value, bool terminal,
         const std::shared_ptr<Node> &prec,const Board& board) : action_position(action_position), min_max(min_max), value(value),
                                              terminal(terminal), prec(prec),simulation(board) {}

    const std::pair<int, int> &getAction_position() const {
        return action_position;
    }
    bool operator < (const std::shared_ptr<Node>& rhs) const;

    void add_next_node(const std::shared_ptr<Node>& to_add){
        next.push_back(to_add);
    }

    const std::vector<std::shared_ptr<Node>> &getNext() const {
        return next;
    }

    const Board &getSimulation() const {
        return simulation;
    }

    int simulate_play(const e_color& color);

    void setAction_position(const std::pair<int, int> &action_position) {
        Node::action_position = action_position;
    }

    e_min_max getMin_max() const {
        return min_max;
    }

    void setMin_max(e_min_max min_max) {
        Node::min_max = min_max;
    }

    int getValue() const {
        return value;
    }

    void setValue(int value) {
        Node::value = value;
    }

    bool isTerminal() const {
        return terminal;
    }

    void setTerminal(bool terminal) {
        Node::terminal = terminal;
    }

    const std::shared_ptr<Node> &getPrec() const {
        return prec;
    }

    void setPrec(const std::shared_ptr<Node> &prec) {
        Node::prec = prec;
    }

    bool isVisited() const {
        return visited;
    }

    void setVisited(bool visited) {
        Node::visited = visited;
    }


};


#endif //OTHELLO_NODE_H
