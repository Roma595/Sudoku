#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "Board.h"

namespace {

    std::vector<int> get_random_numbers() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::shuffle(numbers.begin(), numbers.end(), gen);

        return numbers;
    }

    std::vector<Cell> get_cells() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::vector<Cell> cells;

        for (size_t i = 0; i < 9; ++i){
            for (size_t j = 0; j < 9; ++j){
                cells.push_back(Cell{i,j});
            }
        }

        std::shuffle(cells.begin(), cells.end(), gen);
        return cells;
    }



} // namespace

void Board::set_cell_in_board(size_t row, size_t col, const int num) {
    board[row][col] = num;
}

int Board::get_cell_from_board(size_t row, size_t col) const {
    return board[row][col];
}

size_t Board::get_board_size() const {
    return BOARD_SIZE;
}

void Board::create_inaccessible_cells(){
    for (size_t row = 0; row < 9; ++row){
        for (size_t col = 0; col < 9; ++col){
            if (board[row][col] != 0){
                inaccessible_cells.push_back(Cell{row,col});
            }
        }
    }
}

bool Board::is_cell_unavailable(size_t row, size_t col) const{
    if(std::find(inaccessible_cells.begin(),inaccessible_cells.end(),Cell{row,col}) != inaccessible_cells.end()){
        return true;
    }
    return false;
}

//переписать
bool Board::initialize_board() {
    std::vector<int> numbers = get_random_numbers();

    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num : numbers) {
                    if (is_digit_allowed(row, col, num)) {
                        board[row][col] = num;
                        if (initialize_board()) {
                            return true;
                        }
                        board[row][col] = 0;  // backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool Board::check_cell_in_row_and_col(const size_t row, const size_t col, const int num) {
    for (size_t i = 0; i < 9; ++i) {
        if(row == i || col == i){
            continue;
        }
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }
    return true;
}

bool Board::check_cell_in_square(const size_t row, const size_t col, const int num) {
    size_t square_first_row = 3 * (row / 3);
    size_t square_first_col = 3 * (col / 3);

    for (size_t square_row = 0; square_row < 3; ++square_row) {
        for (size_t square_col = 0; square_col < 3; ++square_col) {
            if(row == square_first_row + square_row && col == square_first_col + square_col){
                continue;
            }
            if (board[square_first_row + square_row][square_first_col + square_col] == num) {
                return false;
            }
        }
    }
    return true;
}

bool Board::is_digit_allowed(const size_t row, const size_t col, int num) {
    if (!check_cell_in_row_and_col(row, col, num) || !check_cell_in_square(row, col, num)) {
        return false;
    }
    return true;
}

bool Board::check_board_is_full() {
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Board::is_valid_board() {
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            if (!is_digit_allowed(row, col, board[row][col])){
                return false;
            }
        }
    }
    return true;
}

int Board::count_solutions() {
    int count = 0;
    std::vector<int> numbers = get_random_numbers();

    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num : numbers) {
                    if (is_digit_allowed(row, col, num)) {
                        board[row][col] = num;
                        count += count_solutions();
                        board[row][col] = 0;
                    }
                }
                return count;
            }
        }
    }
    return 1;
}

void Board::generate_sudoku(int digits_to_remove) {
    std::vector<Cell> cells = get_cells();
    for (auto& cell : cells){
        if (digits_to_remove == 0) {
            break;
        }
        int temp = board[cell.row][cell.col];
        board[cell.row][cell.col] = 0;

        if (count_solutions() != 1) {
            board[cell.row][cell.col] = temp;
        }

        else {
            digits_to_remove--;
        }
    }
}
