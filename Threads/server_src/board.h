#ifndef BOARD_H
#define BOARD_H

#define TABLE_SIZE 3
#define EMPTY ' '

class Board {
private:
    char table[TABLE_SIZE][TABLE_SIZE];

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

public:
    Board() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (int j = 0; j < TABLE_SIZE; j++) {
                table[i][j] = EMPTY;
            }
        }
    }

    char get_cell(int row, int col) const;
    void set_cell(int row, int col, char value);

    Board(Board&&) = default;
    Board& operator=(Board&&) = default;

    ~Board() = default;
};

#endif  // BOARD_H
