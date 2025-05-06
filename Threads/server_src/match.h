#ifndef MATCH_H
#define MATCH_H

#include <condition_variable>
#include <mutex>
#include <string>
#include <utility>

#include "board.h"

#define CROSS 'X'
#define CIRCLE 'O'
#define DRAW 'D'
#define IN_PROGRESS 'I'

class Match {
private:
    std::string party_name;
    Board table;
    char current_turn = CIRCLE;
    char winner = IN_PROGRESS;
    std::condition_variable turn;
    std::mutex mtx;

    const bool is_this_value_wins(char value) const;
    const bool is_full() const;
    const bool is_cell_free(int row, int col) const;

    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;

public:
    explicit Match(const std::string& party_name): party_name(party_name) {}

    void make_move(int row, int col, char value);
    const Board& get_table() const;
    const std::string& get_party_name() const;
    const char has_winner() const;
    const void wait_turn(const char& player_value);
    void finish_turn();

    Match(Match&&) = default;
    Match& operator=(Match&&) = default;

    ~Match() = default;
};

#endif  // MATCH_H
