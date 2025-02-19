#pragma once

#include <vector>

struct Cell {
    size_t row;
    size_t col;

    bool operator==(const Cell& other) const {
        return row == other.row && col == other.col;
    }
};

class Board {

public:
    bool initialize_board();

    bool check_cell_in_row_and_col(size_t row, size_t col, const int num);
    bool check_cell_in_square(size_t row, size_t col, const int num);
    bool is_digit_allowed(size_t row, size_t col, const int num);

    bool is_cell_unavailable(size_t row, size_t col) const;

    void generate_sudoku(int digits_to_remove);
    int count_solutions();
    bool check_board_is_full();
    bool is_valid_board();

    void create_inaccessible_cells();

    size_t get_board_size() const;
    int get_cell_from_board(size_t row, size_t col) const;

    void set_cell_in_board(size_t row, size_t col, const int num);

private:
    std::vector<Cell> inaccessible_cells;
    static const size_t BOARD_SIZE = 9;
    int board[BOARD_SIZE][BOARD_SIZE] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
};
