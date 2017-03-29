//
// Created by johann on 29/03/17.
//

#include "Game.h"

void Game::game_loop() {
        turn_play(white);
        turn_play(black);}

bool Game::is_end() const {
    for (int i{1}; i < ROW - 2; ++i) {
        for (int j{1}; j < COL - 2; ++j) {
            if (getBoard().is_playable(i, j)) { return true; }
        }
    }
    return false;
}

void Game::turn_play(Player &player_to_play) {

    getBoard().display();
    player_to_play.play_turn(board);
    getBoard().display();
    incr_number_of_turn();
}
