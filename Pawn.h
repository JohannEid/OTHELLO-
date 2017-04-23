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
    sf::Sprite pawn_sprite;
    sf::Sprite target_sprite;
    bool is_sprite_changed;
public:
    Tile() {}

    Tile(e_color color);

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

    void setTarget(bool target);

    const sf::Sprite &getPawn_sprite() const {
        return pawn_sprite;
    }

    const sf::Sprite &getTarget_sprite() const {
        return target_sprite;
    }

    bool isIs_sprite_changed() const {
        return is_sprite_changed;
    }

    void setIs_sprite_changed(bool is_sprite_changed) {
        Tile::is_sprite_changed = is_sprite_changed;
    }

    void setSpritePosition(const int &x, const int &y) { pawn_sprite.setPosition(x, y); }

    void setSpritePosition_target(const int &x, const int &y) { target_sprite.setPosition(x, y); }

    void set_sprite(const sf::Texture& texture){pawn_sprite.setTexture(texture);}

    void set_sprite_target(const sf::Texture& texture){target_sprite.setTexture(texture);}


};


#endif //OTHELLO_PAWN_H
