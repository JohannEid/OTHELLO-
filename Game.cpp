//
// Created by johann on 29/03/17.
//

#include "Game.h"


void Game::game_loop(int index_player) {
    sf::Event event;
    int player_index = (index_player != 404) ? index_player : 0;
    int opponent_index;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left
                     && players[player_index]->moveSelection(window, board) != ERROR) {
                opponent_index = (player_index == 1) ? 0 : 1;
                turn_play(*players[player_index], *players[opponent_index]);
                player_index = opponent_index;

            }


        }
        window.clear();
        display();
        window.display();

    }

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
}

void Game::game_menu() {
    std::string ichoice{" "};
    int choice{0};
    int save_starter{404};


    while (true) {
        try {


            game_menu_display();
            std::cin >> ichoice;
            choice = std::stoi(ichoice);
            if (choice == 1) {
                break;
            } else if (choice == 2) {
                players[0] = std::move(std::make_unique<Ai_easy>(Ai_easy(e_color::BLACK)));
                break;
            } else if (choice == 3) {
                players[0] = std::move(std::make_unique<Ai_medium>(Ai_medium(e_color::BLACK)));
                break;
            } else if (choice == 4) {
                load_from_file();
                save_starter = (get_number_of_turns() % 2 == 0) ? 0 : 1;
                break;
            } else {
                throw std::domain_error("Wrong entry");
            }
        }
        catch (std::exception const &e) {
            std::cerr << "Erreur" << e.what() << std::endl;
        }
    }
    (save_starter != QUIT) ? game_loop(save_starter) : game_loop();

}

void Game::game_menu_display() const {
    std::cout << "Welcome to othello" << std::endl;
    std::cout << "1.Start a new game between humans" << std::endl;
    std::cout << "2.Play against easy AI." << std::endl;
    std::cout << "3.Play against medium AI." << std::endl;
    std::cout << "4.Load previous game" << std::endl;
}

Game::Game() {
    window.create(sf::VideoMode(window_width, window_height), "JChess");
    players.push_back(std::make_unique<Player>(Player(e_color::BLACK)));
    players.push_back(std::make_unique<Player>(Player(e_color::WHITE)));
}

void Game::display() {
    window.draw(board.getSprite_board());
    for (int i{1}; i < ROW - 2; ++i)
        for (int j{1}; j < COL - 2; ++j) {
            if (getBoard().getBoard(i, j).getColor() != e_color::NONE) {
                board.set_sprite_position(i, j);
                window.draw(board.getBoard(i, j).getPawn_sprite());
            }


        }
}









