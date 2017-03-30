//
// Created by johann on 29/03/17.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include "Player.h"
#include "Board.h"

class Game {
private:
    Player white = Player(e_color::WHITE);
    Player black = Player(e_color::BLACK);
    Board board;

public:
    void game_loop();

    void turn_play(Player &player_to_play, Player& opponent);

    bool is_end() const;

    const Board &getBoard() const {
        return board;
    }

    const Player &getWhite() const {
        return white;
    }

    const Player &getBlack() const {
        return black;
    }

    void incr_number_of_turn(){board.incrNumberOfTurns();}


};


#endif //OTHELLO_GAME_H
