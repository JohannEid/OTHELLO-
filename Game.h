//
// Created by johann on 29/03/17.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include "Player.h"
#include "Board.h"

class Game {
private:
    std::vector<Player>players {Player(e_color::WHITE), Player(e_color::BLACK)};
    Board board;

    void save() const ;

    char write_in_file(const int& coordx,const int& coordy) const;

public:
    void game_loop();

    bool turn_play(Player &player_to_play, Player& opponent);

    bool is_end() const {return (!getPlayers()[0].is_allowed(board) && !getPlayers()[1].is_allowed(board));}

    const Board &getBoard() const {
        return board;
    }

    const std::vector<Player> &getPlayers() const {
        return players;
    }

    void setPlayers(const std::vector<Player> &players) {
        Game::players = players;
    }


    void incr_number_of_turn(){board.incrNumberOfTurns();}


};


#endif //OTHELLO_GAME_H
