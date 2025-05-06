#include "match.h"

const bool Match::is_cell_free(int row, int col) const { return table.get_cell(row, col) == EMPTY; }

void Match::make_move(int row, int col, char value) {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_cell_free(row, col))
        table.set_cell(row, col, value);
}

const Board& Match::get_table() const { return table; }

const std::string& Match::get_party_name() const { return party_name; }

const bool Match::is_full() const {
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            if (table.get_cell(i, j) == EMPTY)
                return false;
        }
    }
    return true;
}

const bool Match::is_this_value_wins(char value) const {
    // Verifico por filas
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table.get_cell(i, 0) == value && table.get_cell(i, 1) == value &&
            table.get_cell(i, 2) == value) {
            return true;
        }
    }

    // Verificio por columnas
    for (int j = 0; j < TABLE_SIZE; j++) {
        if (table.get_cell(0, j) == value && table.get_cell(1, j) == value &&
            table.get_cell(2, j) == value) {
            return true;
        }
    }

    // Verifico por diagonales
    if (table.get_cell(0, 0) == value && table.get_cell(1, 1) == value &&
        table.get_cell(2, 2) == value) {
        return true;
    }
    if (table.get_cell(0, 2) == value && table.get_cell(1, 1) == value &&
        table.get_cell(2, 0) == value) {
        return true;
    }

    return false;
}

const char Match::has_winner() const {
    if (is_this_value_wins(CROSS))
        return CROSS;
    if (is_this_value_wins(CIRCLE))
        return CIRCLE;
    if (is_full())
        return DRAW;

    return IN_PROGRESS;
}

const void Match::wait_turn(const char& player_value) {
    std::unique_lock<std::mutex> lock(mtx);
    while (player_value != current_turn) turn.wait(lock);
}

void Match::finish_turn() {
    std::lock_guard<std::mutex> lock(mtx);
    current_turn = (current_turn == CROSS) ? CIRCLE : CROSS;
    turn.notify_all();
}
