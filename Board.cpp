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
        (othellier[i][j].getColor()==e_color::WHITE)?rlutil::setColor(rlutil::WHITE):
        (othellier[i][j].getColor()==e_color::BLACK)?rlutil::setColor(rlutil::BLACK):
        rlutil::setColor(rlutil::BLUE);

      std::cout << othellier[i][j].getWidget();
    }
    std::cout<<std::endl;
}

}

bool Board::is_playable(const int &i, const int &j) {
    std::list<std::pair<int,int>> check_coordinates{std::make_pair(1,0), std::make_pair(0,1),
                                                    std::make_pair(-1,0), std::make_pair(0,-1),
                                                    std::make_pair(1,1), std::make_pair(-1,-1)};
    if(getBoard(i,j).getColor()==e_color::NONE){ return false;}
    for(const auto& elem : check_coordinates){
        if(getBoard(i+elem.first,j+elem.second).getColor() == e_color::WHITE
           && getNumber_of_turn()%2 == 0){ return true;}
        else if(getBoard(i+elem.first,j+elem.second).getColor() == e_color::BLACK
           && getNumber_of_turn()%2 == 1){ return true;}
    }
    return false;

}

