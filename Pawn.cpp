//
// Created by johann on 28/03/17.
//

#include "Pawn.h"

void Tile::init_tile(const int &ind_lhs, const int &ind_rhs) {


    if (((ind_lhs == 0) ||(ind_lhs == ROW-1))&& (ind_rhs<= ROW -2&&ind_rhs>=1)){
        setWidget( ind_rhs + '0');
    }
    else if (((ind_rhs == 0) ||(ind_rhs == ROW-1))&& (ind_lhs<= ROW -2 && ind_lhs>=1)) {
        setWidget(ind_lhs + '0' + 16);
    }

}
