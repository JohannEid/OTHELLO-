//
// Created by johann on 29/03/17.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include "Player.h"
#include "Board.h"
#include "Header.h"

class Audio {
private:
    sf::Music background_music;
    sf::SoundBuffer buffer_roll_dice;
    sf::Sound sound_roll_dice;


public:
    void createAudio(const std::string &, const std::string &);

    void playMusic();

    void playSoundEffet();
};


class Game {
private:
    std::vector<std::unique_ptr<Player>> players ;

    Board board;

    sf::RenderWindow window ;

    Audio my_audio;

    void save() const ;

    char write_in_file(const int& coordx,const int& coordy) const;

    void game_menu_display() const;

    e_color write_from_file(const char& c) const;

    void load_from_file();


public:

    Game();
    void game_loop( int index_player = 404);

    void game_menu();


    bool turn_play(Player &player_to_play, Player& opponent);

    bool is_end() const {return (!getPlayers()[0]->is_allowed(board) && !getPlayers()[1]->is_allowed(board));}

    const Board &getBoard() const {
        return board;
    }

    const std::vector<std::unique_ptr<Player>> &getPlayers() const {
        return  players;
    }

    void incr_number_of_turn(){board.incrNumberOfTurns();}

    void set_number_of_turns(int number_of_turn){board.setNumber_of_turn(number_of_turn);}

    int get_number_of_turns() const {return board.getNumber_of_turn();}



    void display(int index_player)  ;



};


#endif //OTHELLO_GAME_H
