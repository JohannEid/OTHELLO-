//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_PAWN_H
#define OTHELLO_PAWN_H
enum class e_color {
    WHITE, BLACK, NONE
};


class Pawn {
private:
    e_color color;
public:
    Pawn(e_color color) : color(color) {}

    e_color getColor() const {
        return color;
    }

    void setColor(e_color color) {
        Pawn::color = color;
    }

};


#endif //OTHELLO_PAWN_H
