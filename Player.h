//
// Created by johann on 29/03/17.
//

#ifndef OTHELLO_PLAYER_H
#define OTHELLO_PLAYER_H


#include "Pawn.h"
#include "Board.h"
#include "Node.h"

class Tree;

class Player {
protected:
    std::string name = "Player";

private:
    e_color color;
    int score = 2;

public:
    Player(e_color color) : color(color) {}

    virtual int play_turn(Board &board_to_play, sf::RenderWindow &window);

    bool is_allowed(const Board &board) const;

    e_color getColor() const {
        return color;
    }

    int getScore() const {
        return score;
    }

    void setScore(int score) {
        Player::score = score;
    }

    int moveSelection(sf::RenderWindow &window, Board &board);

    void show_targets(Board &to_play) const;

    const std::string &getName() const {
        return name;
    }


};

class Ai : public Player {

public:

    Ai(e_color color) : Player(color) { name = "Ai"; }

    int play_turn(Board &board_to_play, sf::RenderWindow &window);

    virtual void choose_play(Board &board_to_play) {}

    virtual std::vector<std::pair<int, int>> list_choices(const Board &board_to_play, bool is_oppenent = false) const;

    void choose_base(Board &board_to_play, std::shared_ptr<Node> &base);


};

class Ai_easy : public Ai {
private:

    void choose_play(Board &board_to_play);

    void display_choice(const std::vector<std::pair<int, int>> &choices) const;

public:
    Ai_easy(e_color color) : Ai(color) { name = "eAi"; }


};

class Ai_medium : public Ai {
private:

    void choose_play(Board &board_to_play);

public:

    Ai_medium(e_color color) : Ai(color) { name = "mAi"; }
};

#endif //OTHELLO_PLAYER_H
