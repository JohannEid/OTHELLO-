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

void Board::change_color(const std::vector<std::pair<int, int>> &coord_to_change,
                         const e_color &temp_color) {
    for (const auto &elem : coord_to_change) {
        set_color(elem.first, elem.second, temp_color);
    }
}


std::vector<std::pair<int, int>> Board::get_encirclement
        (const int &initial_posx, const int &initial_posy, const e_color &color) const {

    std::vector<std::pair<int, int>> temp;
    std::vector<std::pair<int, int>> post_temp;
    int coordx{0};
    int coordy{0};
    bool keep{false};
    e_color temp_color{color};
    e_color opposite_color = (temp_color == e_color::WHITE) ? e_color::BLACK : e_color::WHITE;


    for (const auto &elem: check_coordinates) {
        coordx = initial_posx;
        coordy = initial_posy;

        while (true) {
            if (((coordx + elem.first <= ROW - 2) && coordx + elem.first >= 1)
                && (coordy + elem.second <= COL - 2 && coordy + elem.second >= 1)) {
                coordx += elem.first;
                coordy += elem.second;
                if (getBoard(coordx, coordy).getColor() == temp_color) {
                    keep = true;
                    break;
                } else if (getBoard(coordx, coordy).getColor() == e_color::NONE) {
                    keep = false;
                    break;
                } else {
                    temp.push_back(std::make_pair(coordx, coordy));
                }
            } else { break; }
        }
        if (keep) {
            post_temp.insert(post_temp.end(), temp.begin(), temp.end());
            temp.clear();
        } else { temp.clear(); }

    }
    return post_temp;
}

void Board::display(const e_color &color, const int &number_of_color_change) const {
    std::string s_color = (color == e_color::WHITE) ? "White" : "Black";
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
    std::cout << "Turn of " << s_color << std::endl;
    for (int i{0}; i < COL; ++i) {
        for (int j{0}; j < ROW; ++j) {
            (othellier[i][j].getColor() == e_color::WHITE) ? rlutil::setColor(rlutil::WHITE) :
            (othellier[i][j].getColor() == e_color::BLACK) ? rlutil::setColor(rlutil::BLACK) :
            (othellier[i][j].isTarget() ) ? rlutil::setColor(rlutil::RED):
            rlutil::setColor(rlutil::YELLOW);

            std::cout << getBoard(i, j).getWidget();
        }
        std::cout << std::endl;
    }

}

bool Board::is_playable(const int &coordx, const int &coordy, e_color play_color) const {
    int checkx{0};
    int checky{0};
    bool is_playable;
    e_color opposite_color = (play_color == e_color::WHITE) ? e_color::BLACK : e_color::WHITE;
    if (getBoard(coordx, coordy).getColor() == opposite_color) { return false; }
    for (const auto &elem : check_coordinates) {
        checkx = coordx + elem.first;
        checky = coordy + elem.second;
        is_playable = true;
        if(getBoard(checkx,checky).getColor() != opposite_color){ continue;}

       do{
            if (((checkx + elem.first <= ROW - 2) && checkx + elem.first >= 1)
                && (checky + elem.first <= COL - 2 && checky + elem.first >= 1)) {
                checkx += elem.first;
                checky += elem.second;
            } else {
                is_playable = false;
                break; }
        } while(getBoard(checkx,checky).getColor() != play_color);
    if(is_playable){ return true;}
    }
    return false;
}
