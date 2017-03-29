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
public:
    Player(e_color color) : color(color) {}

    void play_turn(Board &board_to_play);

    e_color getColor() const {
        return color;
    }
};


#endif //OTHELLO_PLAYER_H
