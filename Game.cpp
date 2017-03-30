//
// Created by johann on 29/03/17.
//

#include "Game.h"

void Game::game_loop() {

    while (!(!getWhite().is_allowed(board) && !getBlack().is_allowed(board))) {
        if (getWhite().is_allowed(board)) { turn_play(white,black); }
        else { std::cout << "White can't play" << std::endl; };
        if (getBlack().is_allowed(board)) { turn_play(black,white); }
        else { std::cout << "Black can't play" << std::endl; };
    }

}

void Game:: turn_play(Player &player_to_play, Player& opponent) {
    int number_of_color_change{1};
    getBoard().display(player_to_play.getColor());
     number_of_color_change = player_to_play.play_turn(board);
    getBoard().display(player_to_play.getColor());
    incr_number_of_turn();
    player_to_play.setScore(player_to_play.getScore()+number_of_color_change);
    opponent.setScore(opponent.getScore()+number_of_color_change);

}
