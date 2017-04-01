//
// Created by johann on 28/03/17.
//

#include "Board.h"
#include "Player.h"

Board::Board() {

    othellier.resize(COL, std::vector<Tile>(ROW, Tile()));
    for (int i{0}; i < COL; ++i) {
        for (int j{0}; j < ROW; ++j) {
            othellier[i][j].init_tile(i, j);
        }
    }

}

void Board::display(const e_color &color, const int &number_of_color_change) const {
    std::string s_color = (color == e_color::WHITE) ? "White" : "Black";
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
    std::cout << "Turn of " << s_color << std::endl;
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

bool Board::is_playable(int &coordx, int &coordy, const e_color &player_color) const {

    if (getBoard(coordx, coordy).getColor() != e_color::NONE) { return false; }
    else if (!get_encirclement(coordx, coordy, player_color).empty()) { return true; }

    return false;

}

void Board::change_color(const std::vector<std::pair<int, int>> &coord_to_change,
                         const e_color &temp_color) {
    for (const auto &elem : coord_to_change) {
        othellier[elem.first][elem.second].setColor(temp_color);
    }
}


std::vector<std::pair<int, int>> Board::get_encirclement
        (int &coordx, int &coordy, const e_color color) const {
    std::list<std::pair<int, int>> check_coordinates{std::make_pair(1, 0), std::make_pair(0, 1),
                                                     std::make_pair(-1, 0), std::make_pair(0, -1),
                                                     std::make_pair(1, 1), std::make_pair(-1, -1)};
    std::vector<std::pair<int, int>> temp;
    int initial_posx = coordx;
    int initial_posy = coordy;
    e_color temp_color{color};
    e_color opposite_color = (temp_color == e_color::WHITE) ? e_color::BLACK : e_color::WHITE;


    for (const auto &elem: check_coordinates) {
        coordx = initial_posx;
        coordy = initial_posy;

        while (true) {
            if (((coordx + elem.first <= ROW - 2) && coordx + elem.first >= 1)
                && (coordy + elem.second <= COL - 2 && coordy + elem.second >= 1)) {
                coordx += elem.first;
                coordx += elem.second;
            }
            if (getBoard(coordx, coordy).getColor() == temp_color) { break; }
            else { temp.push_back(std::make_pair(coordx, coordy)); }
        }

    }
    return temp;
}

