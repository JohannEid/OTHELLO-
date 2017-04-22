//
// Created by johann on 28/03/17.
//

#include "Pawn.h"

void Tile::init_tile(const int &ind_lhs, const int &ind_rhs) {


    if (((ind_lhs == 0) || (ind_lhs == ROW - 1)) && (ind_rhs <= ROW - 2 && ind_rhs >= 1)) {
        setWidget(ind_rhs + '0');
    } else if (((ind_rhs == 0) || (ind_rhs == ROW - 1)) && (ind_lhs <= ROW - 2 && ind_lhs >= 1)) {
        setWidget(ind_lhs + '0' + 16);
    } else if ((ind_rhs == 5 && ind_lhs == 4) || (ind_rhs == 4 && ind_lhs == 5)) {
        setColor(e_color::BLACK);
        setWidget('O');
    } else if ((ind_rhs == 4 && ind_lhs == 4) || (ind_rhs == 5 && ind_lhs == 5)) {
        setColor(e_color::WHITE);
        setWidget('O');
    }
    else{
        setColor(e_color::NONE);
    }

}

void Tile::setColor(e_color color) {

    //std::cout <<"called walla"<<std::endl;
    (color != e_color::NONE) ? setWidget('O') : setWidget('\0');
    Tile::color = color;
    if (Tile::color == e_color::BLACK) { assert(pawn_texture.loadFromFile("sprites/chinese_flag.png")); }
    else { assert(pawn_texture.loadFromFile("sprites/usa_flag.png")); }
    pawn_sprite.setTexture(pawn_texture);

}

void Tile::setTarget(bool target) {
    assert(target_texture.loadFromFile("sprites/target.png"));
    target_sprite.setTexture(target_texture);
    Tile::target = target;

}

Tile::Tile(e_color color) {
    setColor(color);
}



