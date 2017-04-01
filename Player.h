//
// Created by johann on 29/03/17.
//

#ifndef OTHELLO_PLAYER_H
#define OTHELLO_PLAYER_H


#include "Pawn.h"
#include "Board.h"

class Player {
private:
    e_color color;
    int score = 2;

    void show_targets(Board &to_play) const;

    void player_mvt(Board &board, const int &base_pos_x, const int &base_pos_y);

    void
    handle_mvt(Board &board,const std::pair<int, int> &move_coord);


public:
    Player(e_color color) : color(color) {}

    int play_turn(Board &board_to_play);

    bool is_allowed(const Board &board) const;

    e_color getColor() const {
        return color;
    }

    int getScore() const {
        return score;
    }

    void setScore(int score) {
        Player::score = score;
    }
};


#endif //OTHELLO_PLAYER_H
