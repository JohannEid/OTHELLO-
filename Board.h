//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include "Header.h"
#include "Pawn.h"


using matrice = std::vector<std::vector<Tile>>;

class Board {
private:
    matrice othellier;
    int number_of_turn = 0;
public:
    Board();

    bool is_playable(const int &i, const int &j, const e_color& player_color) const;

    void display(const e_color& color,const int& number_of_color_change = 0) const;

    int change_color(int i, int j,const e_color color);

    const Tile &getBoard(const int &i, const int &j) const { return othellier[i][j]; }

    int getNumber_of_turn() const {
        return number_of_turn;
    }

    void incrNumberOfTurns() {
        number_of_turn++;
    }

    void set_color(const int &i, const int &j, const e_color& color) {
        othellier[i][j].setColor(color);
    }
};


#endif //OTHELLO_BOARD_H
