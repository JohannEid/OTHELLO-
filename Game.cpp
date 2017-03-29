//
// Created by johann on 29/03/17.
//

#include "Game.h"

void Game::game_loop() {

        if(getWhite().is_allowed(board)) {turn_play(white);}
        else{std::cout << "White can't play" << std::endl;};
        if(getBlack().is_allowed(board)) {turn_play(black);}
        else{std::cout << "Black can't play" << std::endl;};

}

void Game::turn_play(Player &player_to_play) {
    std::string color = (player_to_play.getColor() == e_color::WHITE) ? "White" : "Black";
    std::cout << "Turn of " << color << std::endl;
    getBoard().display();
    player_to_play.play_turn(board);
    getBoard().display();
    incr_number_of_turn();
}
