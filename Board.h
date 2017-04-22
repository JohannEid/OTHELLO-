//
// Created by johann on 28/03/17.
//

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include "Header.h"
#include "Pawn.h"


using matrice = std::vector<std::vector<Tile>>;

class Board {
private:
    matrice othellier;
    int number_of_turn = 0;
    std::pair<int, int> base = std::make_pair(1, 1);
    sf::Sprite sprite_board;
    sf::Texture texture_board;
    std::vector<std::pair<int, int>> white_pawn = {std::make_pair(4, 4), std::make_pair(5, 5)};
    std::vector<std::pair<int, int>> black_pawn = {std::make_pair(4, 5), std::make_pair(5, 4)};

public:
    Board();

    bool is_playable(const int &coordx, const int &coordy, e_color play_color) const;

    std::vector<std::pair<int, int>> get_encirclement(const int &coordx, const int &coordy, const e_color &color) const;

    void change_color(const std::vector<std::pair<int, int>> &coord_to_change, const e_color &temp_color);

    const Tile &getBoard(int i, int j) const { return othellier[i][j]; }

    int getNumber_of_turn() const {
        return number_of_turn;
    }

    void incrNumberOfTurns() {
        number_of_turn++;
    }

    void set_color(const int &coordx, const int &coordy, const e_color &color);

    void setTarget(const int &coordx, const int &coordy, const bool &is_target) {
        othellier[coordx][coordy].setTarget(is_target);
    }

    const std::pair<int, int> &getBase() const {
        return base;
    }

    void setBase(const std::pair<int, int> &base) {
        Board::base = base;
    }

    void setNumber_of_turn(int number_of_turn) {
        Board::number_of_turn = number_of_turn;
    }

    const sf::Sprite &getSprite_board() const {
        return sprite_board;
    }

    void set_sprite_position(const int &i, const int &j) {
        othellier[i][j].setSpritePosition((i - 1) * square_size + SHIFTX + (i - 1) * 5,
                                          (j - 1) * square_size + SHIFY + (j - 1) * 3);
    }

    void set_sprite_position_target(const int &i, const int &j) {
        othellier[i][j].setSpritePosition_target((i - 1) * square_size + SHIFTX + (i - 1) * 5,
                                                 (j - 1) * square_size + SHIFY + (j - 1) * 3);
    }


    void display_(const e_color &color, const int &value, const int &indent) const;

    void reinitialise();

    void reintialise_pawn_track(
            const std::vector<std::pair<int, int>> &black_pawn = {std::make_pair(4, 5), std::make_pair(5, 4)},
            const std::vector<std::pair<int, int>> &white_pawn = {std::make_pair(4, 4), std::make_pair(5, 5)});

    const std::vector<std::pair<int, int>> &getWhite_pawn() const {
        return white_pawn;
    }

    const std::vector<std::pair<int, int>> &getBlack_pawn() const {
        return black_pawn;
    }

    bool is_stable() const;

    void set_board_sprite(sf::Texture& texure){sprite_board.setTexture(texure);}

    void set_sprite(const sf::Texture& texture,const int& coordx,const int& coordy);

    void set_sprite_target(const sf::Texture& texture,const int& coordx,const int& coordy);


    //   friend std::ostream& operator<< (std::ostream& stream, const Board& matrix);

};


#endif //OTHELLO_BOARD_H
