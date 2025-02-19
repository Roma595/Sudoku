#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Game.h"
#include "Board.h"

const unsigned int MAIN_WINDOW_WIDTH = 1080;
const unsigned int MAIN_WINDOW_HEIGHT = 720;
const std::string MAIN_WINDOW_TITLE = "Sudoku";

const unsigned int FINAL_WINDOW_WIDTH = 500;
const unsigned int FINAL_WINDOW_HEUGHT = 340;
const std::string FINAL_WINDOW_TITLE = "RESULT";

const sf::String WINNING_MESSAGE = sf::String("You win!");
const sf::String LOSING_MESSAGE = sf::String("You lost");

const sf::Color BACKGROUD_WINDOW_COLOR = sf::Color::White;
const sf::Color UNAWAILABLE_NUMBER_COLOR = sf::Color::Black;
const sf::Color AWAILABLE_NUMBER_COLOR = sf::Color::Blue;

const sf::Color SELECTION_CELL_COLOR = sf::Color::Green;
const sf::Color GRID_EDGE_COLOR = sf::Color::Blue;

const sf::Color WINNING_TEXT_COLOR = sf::Color::Green;
const sf::Color LOSING_TEXT_COLOR = sf::Color::Red;

//не получается поставить не абсолютный путь
const sf::Font TUFFY_FONT = sf::Font("C:/Users/kotko/Documents/GitHub/Sudoku/SUDOKU/resources/Tuffy.ttf");
const unsigned int FONT_SIZE = 50;

const unsigned int GRID_WIDTH = 640;
const unsigned int GRID_HEIGHT = 640;

const unsigned int BOARD_SIZE = 9;
const unsigned int CELL_SIZE = 70;
const unsigned int SELECTION_CELL_SIZE = 65;

const unsigned int MARGIN_LEFT_GRID = 150;
const unsigned int MARGIN_TOP_GRID = 10;

const unsigned int MARGIN_LEFT_CELL_NUMBER = 20;
const unsigned int MARGIN_TOP_CELL_NUMBER = 10;

const unsigned int MARGIN_SELECTION_CELL = 5;

const unsigned int MARGIN_FINAL_TEXT_LEFT = 140;
const unsigned int MARGIN_FINAL_TEXT_TOP = 50;

const unsigned int SQUARE_EDGE_THICKNESS = 10;
const unsigned int GRID_EDGE_THICKNESS = 5;

const unsigned int DIGITS_TO_REMOVE = 40;

enum Game_state{
    PLAYING,
    END
};

namespace {

    void draw_grid(sf::RenderWindow& window) {
        sf::RectangleShape column;
        sf::RectangleShape row;

        column.setFillColor(GRID_EDGE_COLOR);
        row.setFillColor(GRID_EDGE_COLOR);

        for (size_t i = 0; i < BOARD_SIZE + 1; ++i) {
            column.setSize(sf::Vector2f(GRID_EDGE_THICKNESS, GRID_HEIGHT));
            row.setSize(sf::Vector2f(GRID_WIDTH, GRID_EDGE_THICKNESS));

            if (i % 3 == 0) {
                column.setSize(sf::Vector2f(SQUARE_EDGE_THICKNESS, GRID_HEIGHT));
                row.setSize(sf::Vector2f(GRID_WIDTH, SQUARE_EDGE_THICKNESS));
            }

            row.setPosition(sf::Vector2f(MARGIN_LEFT_GRID, MARGIN_TOP_GRID + i * CELL_SIZE));
            column.setPosition(sf::Vector2f(MARGIN_LEFT_GRID + i * CELL_SIZE, MARGIN_TOP_GRID));

            window.draw(row);
            window.draw(column);
        }
    }

    void fill_grid(sf::RenderWindow& window, const Board& board) {
        for (size_t row = 0; row < BOARD_SIZE; ++row) {
            for (size_t col = 0; col < BOARD_SIZE; ++col) {
                if (board.get_cell_from_board(row, col) == 0){
                    continue;
                }
                sf::Text number(TUFFY_FONT, sf::String(std::to_string(board.get_cell_from_board(row, col))), FONT_SIZE);

                number.setFillColor(UNAWAILABLE_NUMBER_COLOR);

                if (!board.is_cell_unavailable(row, col)){
                    number.setFillColor(AWAILABLE_NUMBER_COLOR);
                }
                number.setPosition(sf::Vector2f(MARGIN_LEFT_GRID + col * CELL_SIZE + MARGIN_LEFT_CELL_NUMBER,
                                    MARGIN_TOP_GRID + row * CELL_SIZE + MARGIN_TOP_CELL_NUMBER));

                window.draw(number);
            }
        }
    }

    void draw_selection_cell(sf::RenderWindow &window, const Board& board, size_t row, size_t col){
        if (row >= 0 && row < BOARD_SIZE &&
            col >= 0 && col < BOARD_SIZE &&
            !board.is_cell_unavailable(row,col)){

            sf::RectangleShape cell(sf::Vector2f(SELECTION_CELL_SIZE, SELECTION_CELL_SIZE));
            cell.setFillColor(SELECTION_CELL_COLOR);
            cell.setPosition(sf::Vector2f(MARGIN_LEFT_GRID + col * CELL_SIZE + MARGIN_SELECTION_CELL,
                                        MARGIN_TOP_GRID + row * CELL_SIZE + MARGIN_SELECTION_CELL));
            window.draw(cell);
        }
    }

    int key_code_to_digit(sf::Keyboard::Key key) {
        switch(key) {
            case sf::Keyboard::Key::Num1: return 1;
            case sf::Keyboard::Key::Num2: return 2;
            case sf::Keyboard::Key::Num3: return 3;
            case sf::Keyboard::Key::Num4: return 4;
            case sf::Keyboard::Key::Num5: return 5;
            case sf::Keyboard::Key::Num6: return 6;
            case sf::Keyboard::Key::Num7: return 7;
            case sf::Keyboard::Key::Num8: return 8;
            case sf::Keyboard::Key::Num9: return 9;
        }
        return 0;
    }

    void edit_number(Board& board, sf::Keyboard::Key key, size_t row, size_t col) {
        if (!board.is_cell_unavailable(row, col)){
            board.set_cell_in_board(row, col, key_code_to_digit(key));
        }
    }

    void draw_final_screen(Board& board) {
        sf::RenderWindow window(sf::VideoMode({FINAL_WINDOW_WIDTH, FINAL_WINDOW_WIDTH}), FINAL_WINDOW_TITLE, sf::Style::Close);

        sf::Text text(TUFFY_FONT, WINNING_MESSAGE, FONT_SIZE);
        text.setFillColor(WINNING_TEXT_COLOR);

        if (!board.is_valid_board()){
            text.setString(LOSING_MESSAGE);
            text.setFillColor(LOSING_TEXT_COLOR);
        }

        text.setPosition(sf::Vector2f(MARGIN_FINAL_TEXT_LEFT, MARGIN_FINAL_TEXT_TOP));

        //board.set_cell_in_board(row, col, 0);

        while(window.isOpen()){
            window.clear(BACKGROUD_WINDOW_COLOR);
            window.draw(text);

            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>()){
                    window.close();
                }
            }

            window.display();
        }
    }

} //namespace

void Game::run() {
    auto window = sf::RenderWindow(sf::VideoMode({MAIN_WINDOW_WIDTH , MAIN_WINDOW_HEIGHT}), MAIN_WINDOW_TITLE, sf::Style::Close);
    window.setFramerateLimit(144);

    auto state = Game_state::PLAYING;

    Board board;
    //board.initialize_board();
    board.generate_sudoku(DIGITS_TO_REMOVE);
    board.create_inaccessible_cells();

    size_t row = -1;
    size_t col = -1;

    while (window.isOpen()){

        if (state == Game_state::PLAYING){
            window.clear(BACKGROUD_WINDOW_COLOR);
            draw_selection_cell(window, board, row, col);
            draw_grid(window);
            fill_grid(window, board);
            if (board.check_board_is_full()){
                state = Game_state::END;
            }
        }
        else if (state == Game_state::END){
            draw_final_screen(board);
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>()){
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                col = (mouse_pos.x - MARGIN_LEFT_GRID) / CELL_SIZE;
                row = (mouse_pos.y - MARGIN_TOP_GRID) / CELL_SIZE;
            }
            if (event->is<sf::Event::KeyPressed>()){
                sf::Keyboard::Key key = event->getIf<sf::Event::KeyPressed>()->code;
                edit_number(board, key, row, col);
            }
        }
            window.display();
    }
}


