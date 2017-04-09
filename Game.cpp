//
// Created by johann on 29/03/17.
//

#include "Game.h"

void Game::game_loop() {
    bool end;
    Player *ref_opponent;
    while (!is_end()) {
        for (auto &elem : players) {
            ref_opponent = (elem.getColor() == e_color::WHITE) ? &players[1] : &players[0];
            if (elem.is_allowed(board)) { end = turn_play(elem, *ref_opponent); }
            if(!end){ return;}
        }
    }
}

/*
        if (getBlack().is_allowed(board)) { end = turn_play(black, white); }
        else { std::cout << "Black can't play" << std::endl; };
        if(!end){ break;}
        if (getWhite().is_allowed(board)) { end =  turn_play(white, black); }
        else { std::cout << "White can't play" << std::endl; };

    }
}
*/
bool Game::turn_play(Player &player_to_play, Player &opponent) {
    int score_change{0};
    getBoard().display(player_to_play.getColor());
    score_change = player_to_play.play_turn(board);
    if (score_change == QUIT) { return false; }
    getBoard().display(player_to_play.getColor());
    player_to_play.setScore(player_to_play.getScore() + score_change + 1);
    opponent.setScore(opponent.getScore() - score_change);
    incr_number_of_turn();
    return true;
}

