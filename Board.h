//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include "Header.h"
#include "Pawn.h"

int COL = 8;
int ROW = 8;
using matrice = std::vector<std::vector<std::unique_ptr<Pawn>>>;

class Board {
private:
    matrice othellier;
public:
    Board();

};


#endif //OTHELLO_BOARD_H
