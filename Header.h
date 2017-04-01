//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_HEADER_H
#define OTHELLO_HEADER_H

#include "bits/stdtr1c++.h"
#include "rlutil.h"

const unsigned int COL = 10;
const unsigned int ROW = 10;
const std::list<std::pair<int, int>> check_coordinates{std::make_pair(1, 0), std::make_pair(0, 1),
                                                        std::make_pair(-1, 0), std::make_pair(0, -1),
                                                        std::make_pair(1, 1), std::make_pair(-1, -1)};

#endif //OTHELLO_HEADER_H
