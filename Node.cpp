//
// Created by johann on 11/04/17.
//

#include "Node.h"

#include "Node.h"


Board_reverse Node::simulate_play(e_color &color, Board &board, const int &depth) {
    Board_reverse board_reverse;
    board_reverse.max_score = 2;
    board_reverse.min_score = 2;
    int score{0};
    std::vector<std::pair<int, int>> flip_coordinates;
    e_color new_color = color;

    bool terminal = getLast_moves().size() == depth - 1;
    for (int i{0}; i < getLast_moves().size(); ++i) {

        new_color = (i % 2 == 0) ? color : opposite_color(color);
        flip_coordinates = board.get_encirclement(getLast_moves()[i].first,
                                                  getLast_moves()[i].second,
                                                  new_color);
        board.set_color(getLast_moves()[i].first, getLast_moves()[i].second, new_color);
        board.change_color(flip_coordinates, new_color);
        board_reverse.color_to_none.push_back(getLast_moves()[i]);
        score = (int) flip_coordinates.size() + 1;
        if (new_color == color) { board_reverse.max_score += score; }
        else if (new_color == opposite_color(color)) { board_reverse.min_score += score; }

        if (new_color == opposite_color(color)) {
            for (int i{0}; i < flip_coordinates.size(); ++i) {
                if (board_reverse.mitoma.empty() || board_reverse.matomi.empty()) {
                    board_reverse.mitoma.push_back(flip_coordinates[i]);
                } else if (!is_found(board_reverse.mitoma, flip_coordinates[i]) &&
                           !is_found(board_reverse.matomi, flip_coordinates[i])) {
                    board_reverse.mitoma.push_back(flip_coordinates[i]);
                }
            }
        } else if (new_color == color) {
            for (int i{0}; i < flip_coordinates.size(); ++i) {
                if (board_reverse.mitoma.empty() || board_reverse.matomi.empty()) {
                    board_reverse.matomi.push_back(flip_coordinates[i]);
                } else if (!is_found(board_reverse.mitoma, flip_coordinates[i]) &&
                           !is_found(board_reverse.matomi, flip_coordinates[i])) {
                    board_reverse.matomi.push_back(flip_coordinates[i]);
                }
            }
        }
    }
    board_reverse.value = (terminal) ? heuristic_value(board_reverse, board) : INFINITE;
    return board_reverse;

}

Node::Node(const std::pair<int, int> &action_position, const std::shared_ptr<Node> &prec,
           const int &value) : value(value), prec(prec), action_position(action_position) {
    terminal = (value != INFINITE);
    min_max = (prec->getMin_max() == e_min_max::MAX) ? e_min_max::MIN : e_min_max::MAX;
    last_moves = prec->getLast_moves();
    add_moves(action_position);
}

int Node::heuristic_value(Board_reverse &board_reverse, Board &board) {
    int coin_parity{0};
    int mobility_value{0};
    int corners_captured{0};
    int stability_value{0};
    std::pair<int, int> corner = list_corner(board, e_color::BLACK);
    std::pair<int, int> stability = evaluate_stability(board);

    int max_score{board_reverse.max_score};
    int min_score{board_reverse.min_score};
    int max_mobility{list_mobility(board, e_color::BLACK)};
    int min_mobility{list_mobility(board, e_color::WHITE)};
    int max_corner{corner.first};
    int min_corner{corner.second};
    int max_stable{stability.first};
    int min_stable{stability.second};


    coin_parity = 100 * (max_score - min_score) / (max_score + min_score);
    mobility_value = heuristic_forumula(max_mobility, min_mobility);
    corners_captured = heuristic_forumula(max_corner, min_corner);
    stability_value = heuristic_forumula(max_stable, min_stable);
    return coin_parity + mobility_value + corners_captured + stability_value;


}

int Node::list_mobility(const Board &board_to_play, const e_color &color) const {
    int mobility{0};
    for (int i{1}; i < ROW - 1; ++i) {
        for (int j{1}; j < COL - 1; ++j) {
            if (board_to_play.is_playable(i, j, color)) { ++mobility; }
        }
    }
    return mobility;
}

std::pair<int, int> Node::list_corner(const Board &board_to_play, const e_color &color) const {
    int max_corner_number{0};
    int min_corner_number{0};
    std::vector<std::pair<int, int>> corners{std::make_pair(1, 1), std::make_pair(1, 8),
                                             std::make_pair(8, 1), std::make_pair(8, 8)};
    for (const auto &elem : corners) {
        if (board_to_play.getBoard(elem.first, elem.second).getColor() == color) { ++max_corner_number; }
        else if (board_to_play.getBoard(elem.first, elem.second).getColor() ==
                 opposite_color(color)) { ++min_corner_number; }
    }
    return std::make_pair(max_corner_number, min_corner_number);
}

std::pair<int, int> Node::evaluate_stability(const Board &board) const {
    int max_stable{0};
    int min_stable{0};

    if (!board.is_stable()) {
        return std::make_pair(max_stable, min_stable);
    }

    for (auto &elem : board.getBlack_pawn()) {
        max_stable += evaluate_stability_row(elem.first, elem.second, board);
    }
    for (auto &elem : board.getWhite_pawn()) {
        min_stable += evaluate_stability_row(elem.first, elem.second, board);
    }
    return std::make_pair(max_stable, min_stable);
}

int Node::evaluate_stability_row(const int &coordx, const int &coordy, const Board &board) const {
    int checkx{0};
    int checky{0};

    for (const auto &elem : check_coordinates) {
        checkx = coordx;
        checky = coordy;
        while (true) {
            if (is_in_board(checkx += elem.first, checky += elem.second)) {
                if (board.getBoard(checkx, checky).getColor() == e_color::NONE) {
                    return evaluate_stability_neigh(coordx, coordy, board);
                }

            } else { break; }
        }
    }
    return 1;
}

int Node::evaluate_stability_neigh(const int &coordx, const int &coordy, const Board &board) const {
    e_color color = board.getBoard(coordx, coordy).getColor();
    if ((board.getBoard(coordx + 1, coordy).getColor() == color ||
         board.getBoard(coordx - 1, coordy).getColor() == color)
        && (board.getBoard(coordx, coordy + 1).getColor() == color ||
            board.getBoard(coordx, coordy - 1).getColor() == color)
        && (board.getBoard(coordx + 1, coordy + 1).getColor() == color ||
            board.getBoard(coordx - 1, coordy - 1).getColor() == color)
        && (board.getBoard(coordx - 1, coordy + 1).getColor() == color ||
            board.getBoard(coordx + 1, coordy - 1).getColor() == color)) {
        return 1;
    }
    return 0;
}

int Node::heuristic_forumula(const int &max, const int &min) {
    int value = (max + min != 0) ? 100 * (max - min) / (max + min)
                                 : 0;
    return value;

}



