//
// Created by johann on 28/03/17.
//

#include "Board.h"
Board::Board() {

   othellier.resize(COL, std::vector<Tile>(ROW,Tile()));
   for (int i{0}; i < COL; ++i) {
       for (int j{0}; j < ROW; ++j) {
           othellier[i][j].init_tile(i,j);
       }
   }

}

void Board::display() {
for (int i{0}; i < COL; ++i) {
    for (int j{0}; j < ROW; ++j) {
        std::cout<<othellier[i][j].getWidget();
    }
    std::cout<<std::endl;
}

}
