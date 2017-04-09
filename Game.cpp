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
            if (!end) {
                save();
                return; }
        }
    }
}

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

char Game::write_in_file(const int &coordx, const int &coordy) const {
    switch (getBoard().getBoard(coordx, coordy).getColor()) {
        case e_color::WHITE:
            return 'W';

        case e_color::BLACK:
            return 'B';

        case e_color::NONE:
            return 'X';

    }
}

void Game::save() const {
    std::ofstream save_file("save.txt");
    assert (save_file.is_open());
    for (int i{1}; i < ROW - 2; ++i) {
        for (int j{1}; j < COL - 2; ++j) {
            save_file << write_in_file(i, j);
        }
        save_file << std::endl;
    }
    save_file << getBoard().getNumber_of_turn();
    save_file << getPlayers()[0].getScore()<<std::endl;
    save_file << getPlayers()[1].getScore()<<std::endl;


}

