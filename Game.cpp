//
// Created by johann on 29/03/17.
//

#include "Game.h"

void Game::game_loop() {
    while (!is_end() ) {
        if (getBlack().is_allowed(board)) { turn_play(black, white); }
        else { std::cout << "Black can't play" << std::endl; };
        if (getWhite().is_allowed(board)) { turn_play(white, black); }
        else { std::cout << "White can't play" << std::endl; };
    }
}

void Game::turn_play(Player &player_to_play, Player &opponent) {
    int score_change{0};
    getBoard().display(player_to_play.getColor());
    score_change = player_to_play.play_turn(board);
    getBoard().display(player_to_play.getColor());
    player_to_play.setScore(player_to_play.getScore() + score_change + 1);
    opponent.setScore(opponent.getScore() - score_change);
    incr_number_of_turn();
}

