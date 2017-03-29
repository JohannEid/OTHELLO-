//
// Created by johann on 28/03/17.
//

#include "Board.h"

Board::Board() {

    othellier.resize(COL, std::vector<Tile>(ROW, Tile()));
    for (int i{0}; i < COL; ++i) {
        for (int j{0}; j < ROW; ++j) {
            othellier[i][j].init_tile(i, j);
        }
    }

}

void Board::display() const {
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
    for (int i{0}; i < COL; ++i) {
        for (int j{0}; j < ROW; ++j) {
            (othellier[i][j].getColor() == e_color::WHITE) ? rlutil::setColor(rlutil::WHITE) :
            (othellier[i][j].getColor() == e_color::BLACK) ? rlutil::setColor(rlutil::BLACK) :
            rlutil::setColor(rlutil::BLUE);

            std::cout << getBoard(i, j).getWidget();
        }
        std::cout << std::endl;
    }

}

bool Board::is_playable(const int &i, const int &j, const e_color &player_color) const {
    e_color opposite_color = (player_color == e_color::WHITE) ? e_color::BLACK : e_color::WHITE;
    std::list<std::pair<int, int>> check_coordinates{std::make_pair(1, 0), std::make_pair(0, 1),
                                                     std::make_pair(-1, 0), std::make_pair(0, -1),
                                                     std::make_pair(1, 1), std::make_pair(-1, -1)};

    if (getBoard(i, j).getColor() != e_color::NONE) { return false; }
    for (const auto &elem : check_coordinates) {
        if (getBoard(i + elem.first, j + elem.second).getColor() == opposite_color) { return true; }

    }
    return false;

}

void Board::change_color(int coordx, int coordy, const e_color &temp_color) {
    std::list<std::pair<int, int>> check_coordinates{std::make_pair(1, 0), std::make_pair(0, 1),
                                                     std::make_pair(-1, 0), std::make_pair(0, -1),
                                                     std::make_pair(1, 1), std::make_pair(-1, -1)};
    std::vector<std::pair<int, int>> temp;
    int initial_posx = coordx;
    int initial_posy = coordy;
    e_color opposite_color = (temp_color == e_color::WHITE) ? e_color::WHITE : e_color::BLACK;


    for (const auto &elem: check_coordinates) {
        coordx = initial_posx;
        coordy = initial_posy;
        while (getBoard(coordx += elem.first, coordy += elem.second).getColor() == opposite_color) {

            temp.push_back(std::make_pair(coordx, coordy));
        }
        std::cout << coordx  << coordy << std::endl;
        if (getBoard(coordx-1, coordy-1).getColor() == temp_color) {
            for (auto &elem_ : temp) {
                std::cout << "yo"<<std::endl;
                othellier[elem_.first-1][elem_.second-1].setColor(temp_color);
            }
            temp.clear();
        } else {
            temp.clear();
        }

    }

}

