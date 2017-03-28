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
public:
    Board();
    void display();

};


#endif //OTHELLO_BOARD_H
