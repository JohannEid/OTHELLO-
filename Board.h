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
    std::pair<int,int> base = std::make_pair(1,1);

public:
    Board();

    bool is_playable(const int& coordx,const int& coordy,e_color play_color) const ;

    void display(const e_color &color, const int &number_of_color_change = 0) const;

    std::vector<std::pair<int, int>> get_encirclement (const int &coordx, const int &coordy, const e_color& color) const;

    void change_color(const std::vector<std::pair<int, int>> &coord_to_change, const e_color &temp_color);

   const Tile& getBoard( int i,  int j) const { return othellier[i][j]; }

    int getNumber_of_turn() const {
        return number_of_turn;
    }

    void incrNumberOfTurns() {
        number_of_turn++;
    }

    void set_color(const int &coordx, const int &coordy, const e_color &color) {
        othellier[coordx][coordy].setColor(color);
    }

    void setTarget(const int& coordx, const int& coordy,const bool& is_target){
        othellier[coordx][coordy].setTarget(is_target);
    }

    const std::pair<int, int> &getBase() const {
        return base;
    }

    void setBase(const std::pair<int, int> &base) {
        Board::base = base;
    }

    void setNumber_of_turn(int number_of_turn) {
        Board::number_of_turn = number_of_turn;
    }
};


#endif //OTHELLO_BOARD_H
