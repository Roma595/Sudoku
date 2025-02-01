#pragma once 

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

class Board {

public:
    bool initialize_board();
    bool is_valid_cell(int row, int col, int num);
    bool check_board_is_full();
    bool check_board_is_valid();
    void generate_sudoku(int difficulty = 40);
    int count_solutions();


    int board[9][9] = {0};
};