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

    bool player_input(Board &board);

    void handle_mvt(Board &board, const std::vector<bool> &key_states);

    std::pair<int, int> handle_key_states(const std::vector<bool> &key_states);

    void update_key_state(Board &board, std::vector<bool> &key_states, const keys &key);

    void display_player_score(const Board &board) const;



public:
    Player(e_color color) : color(color) {}

    virtual int play_turn(Board &board_to_play,sf::RenderWindow& window);

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
    int moveSelection(sf::RenderWindow &window,Board& board);

    void show_targets(Board &to_play) const;

    const std::string &getName() const {
        return name;
    }


};

class Ai : public Player {

public:

    Ai(e_color color) : Player(color) {name = "Ai";}

    int play_turn(Board &board_to_play,sf::RenderWindow& window);

    virtual void choose_play(Board &board_to_play) {}

    virtual std::vector<std::pair<int, int>> list_choices(Board &board_to_play, bool is_oppenent = false) const;



};

class Ai_easy : public Ai {
private:

    void choose_play(Board &board_to_play);

public:
    Ai_easy(e_color color) : Ai(color) {}


};

class Ai_medium : public Ai {
private:

    void choose_play(Board &board_to_play);

public:

    Ai_medium(e_color color) : Ai(color) {}








};

#endif //OTHELLO_PLAYER_H
