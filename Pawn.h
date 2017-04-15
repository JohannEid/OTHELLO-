//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_PAWN_H
#define OTHELLO_PAWN_H

#include "Header.h"

class Tile {
private:
    e_color color = e_color::NONE;
    char widget = '\0';
    bool target = false;
    sf::Texture pawn_texture;
    sf::Sprite pawn_sprite;
public:
    Tile() {}

    Tile(e_color color) { setColor(color); }

    void init_tile(const int &ind_lhs, const int &ind_rhs);

    char getWidget() const {
        return widget;
    }

    void setWidget(char widget) {
        Tile::widget = widget;
    }

    e_color getColor() const {
        return color;
    }

    void setColor(e_color color);

    bool isTarget() const {
        return target;
    }

    void setTarget(bool target) {
        Tile::target = target;
    }

    const sf::Sprite &getPawn_sprite() const {
        return pawn_sprite;
    }

    void setSpritePosition(const int &x, const int &y) { pawn_sprite.setPosition(x, y); }
};


#endif //OTHELLO_PAWN_H
