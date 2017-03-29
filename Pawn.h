//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_PAWN_H
#define OTHELLO_PAWN_H

#include "Header.h"

enum class e_color {
    WHITE, BLACK, NONE
};


class Tile {
private:
    e_color color = e_color::NONE;
    char widget = '\0';
public:
    Tile(){}
    Tile(e_color color) : color(color) {}
    void init_tile(const int& ind_lhs, const int& ind_rhs);
    char getWidget() const {
        return widget;
    }

    void setWidget(char widget) {
        Tile::widget = widget;
    }

    e_color getColor() const {
        return color;
    }

    void setColor(e_color color)  {
        Tile::color = color;
    }

};



#endif //OTHELLO_PAWN_H
