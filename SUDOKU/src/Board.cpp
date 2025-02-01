#include "Board.h"

std::vector<int> get_random_numbers() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(numbers.begin(), numbers.end(), gen);

    return numbers;
}

std::vector<std::pair<int,int>> get_cells(){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::pair<int,int>> cells;

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cells.push_back(std::make_pair(i, j));
        }
    }
    
    std::shuffle(cells.begin(), cells.end(), gen);
    return cells;
}

bool Board::initialize_board() {
    std::vector<int> numbers = get_random_numbers();

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num : numbers) {
                    if (is_valid_cell(row, col, num)) {
                        board[row][col] = num;
                        if (initialize_board()) {
                            return true;
                        } 
                        else {
                            board[row][col] = 0;  // backtrack
                        }
                    }
                }
                return false;  
            }
        }
    }
    return true; 
}

bool Board::is_valid_cell(int row, int col, int num) {
    for ( int i = 0; i < 9; i++ ) {
        // проверка что в строке и столбце нет такого же числа
        if ( board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // проверка что в квадрате нет такого же числа
    int start_row = 3 * (row / 3);   //0, 3, 6
    int start_col = 3 * (col / 3);   //0, 3, 6

    for ( int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if (board[start_row + i][start_col + j] == num){
                return false;
            }
        }
    }
    return true;
}

bool Board::check_board_is_full() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Board::check_board_is_valid() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] != 0) {
                int num = board[row][col];
                board[row][col] = 0;
                if (!is_valid_cell(row, col, num)) {
                    board[row][col] = num;
                    return false;
                }
                board[row][col] = num;
            }
        }
    }
    return true;
}

int Board::count_solutions() {
    int count = 0;
    std::vector<int> numbers = get_random_numbers();

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num : numbers) {
                    if (is_valid_cell(row, col, num)) {
                        board[row][col] = num;
                        count += count_solutions();
                        board[row][col] = 0;  // backtrack
                    }
                }
                return count;
            }
        }
    }
    return 1;
}

void Board::generate_sudoku(int difficulty) {
    std::vector<std::pair<int,int>> cells = get_cells();
    for (auto& cell : cells){
        if (difficulty == 0){
            break;
        }
        int row = cell.first;
        int col = cell.second;
        int temp = board[row][col];
        board[row][col] = 0;
        
        if (count_solutions() != 1){
            board[row][col] = temp;
        }

        else{
            difficulty--;
        }
    }
}