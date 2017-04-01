//
// Created by johann on 29/03/17.
//

#include "Game.h"

void Game::game_loop() {
    while(!is_end()){
        if (getBlack().is_allowed(board)) { turn_play(black, white); }
        else { std::cout << "Black can't play" << std::endl; };
        incr_number_of_turn();
        if (getWhite().is_allowed(board)) { turn_play(white, black); }
        else { std::cout << "White can't play" << std::endl; };
        incr_number_of_turn();
    }

}

void Game::turn_play(Player &player_to_play, Player &opponent) {
    getBoard().display(player_to_play.getColor());
    player_to_play.play_turn(board);
    getBoard().display(player_to_play.getColor());
}

