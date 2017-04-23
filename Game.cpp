//
// Created by johann on 29/03/17.
//

#include "Game.h"


void Game::game_loop() {
    sf::Sprite sprite;
    my_audio.playMusic();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (state == 0) {
                game_menu();
            } else if (state == 1) {
                game_play();
            }
            if (event.type == sf::Event::Closed)
                window.close();


            if (state == 1) { window.setMouseCursorVisible(false); }
            if (state == 0) { window.setMouseCursorVisible(true); }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && state == 1) {
                save();
                board.reinitialise();
                state = 0;
            }
        }
        custom_cursor(player_index);
        window.clear();
        display(player_index);
        window.display();

    }
    display_score();
    save();
}


bool Game::turn_play(Player &player_to_play, Player &opponent) {
    int score_change{0};
    score_change = player_to_play.play_turn(board, window);
    player_to_play.setScore(player_to_play.getScore() + score_change + 1);
    opponent.setScore(opponent.getScore() - score_change);
    incr_number_of_turn();
    return true;
}

char Game::write_in_file(const int &coordx, const int &coordy) const {
    switch (getBoard().getBoard(coordx, coordy).getColor()) {
        case e_color::WHITE:
            return 'W';

        case e_color::BLACK:
            return 'B';

        case e_color::NONE:
            return 'X';

    }
}

e_color Game::write_from_file(const char &c) const {
    switch (c) {
        case 'W':
            return e_color::WHITE;

        case 'B':
            return e_color::BLACK;

        case 'X':
            return e_color::NONE;
    }
}


void Game::save() const {
    std::ofstream save_file("save.txt");
    int ai_number = (getPlayers()[0]->getName() == "eAi") ? 1 :
                    (getPlayers()[0]->getName() == "mAi") ? 2 :
                    0;
    assert(save_file.is_open());
    for (int i{1}; i < ROW - 1; ++i) {
        for (int j{1}; j < COL - 1; ++j) {
            save_file << write_in_file(i, j);
        }
        save_file << std::endl;
    }
    save_file << std::endl;
    save_file << getBoard().getNumber_of_turn() << std::endl;
    save_file << getPlayers()[0]->getScore() << std::endl;
    save_file << getPlayers()[1]->getScore() << std::endl;
    save_file << ai_number << std::endl;
    save_file.close();
}

void Game::load_from_file() {
    std::ifstream load_file("save.txt");
    char c{' '};
    int coordx{1};
    int coordy{1};
    int number{0};
    std::vector<int> temp;
    assert(load_file.is_open());

    while (load_file.get(c)) {


        if (coordx < 9) {
            if (c == '\n') { coordx++; }
            else {
                board.set_color(coordx, coordy, write_from_file(c));
                coordy = (coordy == ROW - 2) ? 1 : coordy + 1;
            }

        } else {
            while (load_file >> number) {
                temp.push_back(number);
            }
        }


    }
    load_file.close();
    set_number_of_turns(temp[0]);
    players[0]->setScore(temp[1]);
    players[1]->setScore(temp[2]);
    if (temp[3] == 1) { players[0] = std::move(std::make_unique<Ai_easy>(Ai_easy(e_color::BLACK))); }
    else if (temp[3] == 2) { players[0] = std::move(std::make_unique<Ai_medium>(Ai_medium(e_color::BLACK))); }
}

void Game::game_menu() {
    sf::Vector2i mouse_pos_ = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos = window.mapPixelToCoords(mouse_pos_);

    if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {

        if ((mouse_pos.x >= HvHxl && mouse_pos.x <= HvHxr) && (mouse_pos.y >= HvHyl && mouse_pos.y <= HvHyr)) {
            players[0] = std::move(std::make_unique<Player>(Player(e_color::BLACK)));
            players[1] = std::move(std::make_unique<Player>(Player(e_color::WHITE)));
            state = 1;
        } else if ((mouse_pos.x >= AIexl && mouse_pos.x <= AIexr) && (mouse_pos.y >= AIeyl && mouse_pos.y <= AIeyr)) {
            players[0] = std::move(std::make_unique<Ai_easy>(Ai_easy(e_color::BLACK)));
            players[1] = std::move(std::make_unique<Player>(Player(e_color::WHITE)));
            state = 1;
        } else if ((mouse_pos.x >= AImxl && mouse_pos.x <= AImxr) && (mouse_pos.y >= AImyl && mouse_pos.y <= AImyr)) {
            players[0] = std::move(std::make_unique<Ai_medium>(Ai_medium(e_color::BLACK)));
            players[1] = std::move(std::make_unique<Player>(Player(e_color::WHITE)));
            state = 1;
        } else if ((mouse_pos.x >= AIhxl && mouse_pos.x <= AIhxr) && (mouse_pos.y >= AIhyl && mouse_pos.y <= AIhyr)) {
            window.close();
        } else if ((mouse_pos.x >= SAVExl && mouse_pos.x <= SAVExr) &&
                   (mouse_pos.y >= SAVEyl && mouse_pos.y <= SAVEyr)) {
            load_from_file();
            player_index = (get_number_of_turns() % 2 == 0) ? 0 : 1;
            state = 1;
        }
    }

}


Game::Game() {
    texture_manager.load_texture();
    load_textures();
    window.create(sf::VideoMode(window_width, window_height), "Othello");
    my_audio.createAudio("sounds/satie_je_te_veux.ogg", "sounds/redneck_roll_dice.wav");
    players.push_back(std::make_unique<Player>(Player(e_color::BLACK)));
    players.push_back(std::make_unique<Player>(Player(e_color::WHITE)));
    board.set_board_sprite(texture_manager.texture[4]);
}

void Game::display(int index_player) {
    if (state == 0) {
        window.draw(sprite[2]);
    } else if (state == 1) {
        players[index_player]->show_targets(board);
        window.draw(board.getSprite_board());
        window.draw(sprite[index_player]);
        for (int i{1}; i < ROW - 1; ++i)
            for (int j{1}; j < COL - 1; ++j) {
                if (getBoard().getBoard(i, j).getColor() != e_color::NONE) {
                    if (board.getBoard(i, j).getColor() == e_color::BLACK && !board.getBoard(i,j).isIs_sprite_changed()) {
                        board.set_sprite(texture_manager.texture[0], i, j);
                        board.set_sprite_changed(i,j, true);

                    } else if (board.getBoard(i, j).getColor() == e_color::WHITE&& !board.getBoard(i,j).isIs_sprite_changed()) {
                        board.set_sprite(texture_manager.texture[1], i, j);
                        board.set_sprite_changed(i,j, true);

                    }
                    board.set_sprite_position(i, j);
                    window.draw(board.getBoard(i, j).getPawn_sprite());
                } else if (getBoard().getBoard(i, j).isTarget()) {
                    board.set_sprite_target(texture_manager.texture[2], i, j);
                    board.set_sprite_position_target(i, j);
                    window.draw(board.getBoard(i, j).getTarget_sprite());
                }


            }

    }

}

void Game::custom_cursor(const int &player_index) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    sprite[player_index].setPosition(mouse_pos.x, mouse_pos.y);
}

void Game::load_textures() {

        sprite[0].setTexture(texture_manager.texture[0]);
        sprite[1].setTexture(texture_manager.texture[1]);
    sprite[2].setTexture(texture_manager.texture[3]);




}

void Game::game_play() {
    int opponent_index = (player_index == 1) ? 0 : 1;

    if (is_end()) {
        getchar();
        window.close();
    } else if (!getPlayers()[player_index]->is_allowed(getBoard())) {
        player_index = opponent_index;
    } else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left
               && players[player_index]->moveSelection(window, board) != ERROR) {
        my_audio.playSoundEffet();
        turn_play(*players[player_index], *players[opponent_index]);
        player_index = opponent_index;
    } else if (players[player_index]->getName() != "Player") {
        turn_play(*players[player_index], *players[opponent_index]);
        player_index = opponent_index;
    }


}

void Game::display_score() {
    std::cout << "China has a score of:" << players[0]->getScore() << std::endl;
    std::cout << "US has a score of:" << players[1]->getScore() << std::endl;
}


void Audio::createAudio(const std::string &background_music_file, const std::string &buffer_roll_dice_file) {
    assert(background_music.openFromFile(background_music_file));
    assert(buffer_roll_dice.loadFromFile(buffer_roll_dice_file));
    sound_roll_dice.setBuffer(buffer_roll_dice);
}

void Audio::playMusic() {
    background_music.play();
    background_music.setLoop(true);
}

void Audio::playSoundEffet() {
    sound_roll_dice.play();
}





