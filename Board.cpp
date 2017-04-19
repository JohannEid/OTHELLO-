//
// Created by johann on 28/03/17.
//

#include "Board.h"
#include "Player.h"

Board::Board() {
    assert (texture_board.loadFromFile("sprites/board_v3.png"));
    sprite_board.setTexture(texture_board);
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


    for (const auto &elem: check_coordinates) {
        coordx = initial_posx;
        coordy = initial_posy;

        while (true) {

            if (is_in_board(coordx + elem.first, coordy + elem.second)) {
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
            } else {
                keep = false;
                break; }
        }
        if (keep) {
            post_temp.insert(post_temp.end(), temp.begin(), temp.end());
            temp.clear();
        } else { temp.clear(); }

    }
    return post_temp;
}

bool Board::is_playable(const int &coordx, const int &coordy, e_color play_color) const {
    if(getBoard(coordx,coordy).getColor() ==opposite_color(play_color)){return false;}
return get_encirclement(coordx,coordy,play_color).size() >= 1;

}


void Board::display_ (const e_color &color, const int &number_of_color_change) const {
    std::string s_color = (color == e_color::WHITE) ? "White" : "Black";
    //clearconsole();
    std::cout << "Turn of " << s_color << std::endl;
    for (int i{0}; i < COL; ++i) {
        for (int j{0}; j < ROW; ++j) {
            (i == getBase().first && j == getBase().second) ? rlutil::setColor(rlutil::BLUE) :
            (othellier[i][j].getColor() == e_color::BLACK) ? rlutil::setColor(rlutil::BLACK) :
            (othellier[i][j].getColor() == e_color::WHITE) ? rlutil::setColor(rlutil::WHITE) :
            (othellier[i][j].isTarget()) ? rlutil::setColor(rlutil::RED) :
            rlutil::setColor(rlutil::YELLOW);

            std::cout << getBoard(i, j).getWidget();
        }
        std::cout << std::endl;
    }
}