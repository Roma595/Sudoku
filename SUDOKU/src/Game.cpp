#include "Game.h"
#include "Board.h"

void draw_grid(sf::RenderWindow &window) {
    sf::RectangleShape column;
    sf::RectangleShape row;
    column.setFillColor(sf::Color::Blue);
    row.setFillColor(sf::Color::Blue);
    for ( int i = 0; i <10; ++i){
        column.setSize(sf::Vector2f(5,640));
        row.setSize(sf::Vector2f(640,5));
        if (i % 3 == 0){
            column.setSize(sf::Vector2f(10,640));
            row.setSize(sf::Vector2f(640,10));
        }
        row.setPosition(sf::Vector2f(150,10 + i*70));
        column.setPosition(sf::Vector2f(150 + i*70,10));
        window.draw(row);
        window.draw(column);
    }
}

void fill_grid(sf::RenderWindow &window, Board& board, std::vector<std::pair<int,int>>& inaccessible_cells){
    for( int i = 0; i < 9; ++ i){
        for (int j = 0; j < 9; ++j){
            if (board.board[i][j] == 0){
                continue;
            }
            sf::Font font;
            bool loaf_font = font.openFromFile("C:/Users/kotko/Documents/GitHub/Sudoku/SUDOKU/resources/Tuffy.ttf");    
            sf::Text number(font,sf::String(std::to_string(board.board[i][j])),50U);

            number.setFillColor(sf::Color::Black);
            if (std::find(inaccessible_cells.begin(),inaccessible_cells.end(),std::make_pair(i,j)) == inaccessible_cells.end()){
                number.setFillColor(sf::Color::Blue);
            }
            number.setPosition(sf::Vector2f(150 + j * 70 + 20,10 + i*70 + 10));
            window.draw(number);
        }
    }
    
}

void draw_cell(sf::RenderWindow &window, int x, int y, std::vector<std::pair<int,int>>& inaccessible_cells){
    if (x >= 0 && x < 9 && 
        y >= 0 && y < 9 && 
        std::find(inaccessible_cells.begin(),inaccessible_cells.end(),std::make_pair(y,x)) == inaccessible_cells.end()){

        sf::RectangleShape cell(sf::Vector2f(65,65));
        cell.setFillColor(sf::Color::Green);
        cell.setPosition(sf::Vector2f(150 + x*70+5,10 + y*70 + 5));
        window.draw(cell);
    }
    
}

void edit_number(Board& board, int row, int col, sf::Keyboard::Key key, std::vector<std::pair<int,int>> inaccessible_cells){
    if (std::find(inaccessible_cells.begin(),inaccessible_cells.end(),std::make_pair(row,col)) == inaccessible_cells.end()){
        if (key == sf::Keyboard::Key::Num1){
            board.board[row][col] = 1;
        }
        if (key == sf::Keyboard::Key::Num2){
            board.board[row][col] = 2;
        }
        if (key == sf::Keyboard::Key::Num3){
            board.board[row][col] = 3;
        }
        if (key == sf::Keyboard::Key::Num4){
            board.board[row][col] = 4;
        }
        if (key == sf::Keyboard::Key::Num5){
            board.board[row][col] = 5;
        }
        if (key == sf::Keyboard::Key::Num6){
            board.board[row][col] = 6;
        }
        if (key == sf::Keyboard::Key::Num7){
            board.board[row][col] = 7;
        }
        if (key == sf::Keyboard::Key::Num8){
            board.board[row][col] = 8;
        }
        if (key == sf::Keyboard::Key::Num9){
            board.board[row][col] = 9;
        }
        if (key == sf::Keyboard::Key::Backspace){
            board.board[row][col] = 0;
        }
    }
}

std::vector<std::pair<int,int>> get_inaccessible_cells(Board& board){
    std::vector<std::pair<int,int>> inaccessible_cells;
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (board.board[i][j] != 0){
                inaccessible_cells.push_back({i,j});
            }
        }
    }
    return inaccessible_cells;
}

void Game::run() {
    auto window = sf::RenderWindow(sf::VideoMode({1080u, 720u}), "Sudoku",sf::Style::Close );
    window.setFramerateLimit(144);
    window.setSize(sf::Vector2u(1080, 720));
    
    Board board;
    board.initialize_board();
    board.generate_sudoku();
    std::vector<std::pair<int,int>> inaccessible_cells = get_inaccessible_cells(board);

    int row = -1;
    int col = -1;

    while (window.isOpen()){

        window.clear(sf::Color::White);
        draw_cell(window, col, row, inaccessible_cells);
        draw_grid(window);
        fill_grid(window, board, inaccessible_cells);

        if(board.check_board_is_full()){
            sf::Font font;
            bool load_font = font.openFromFile("C:/Users/kotko/Documents/GitHub/Sudoku/SUDOKU/resources/Tuffy.ttf");
            sf::Text text(font,sf::String("You won!"),50);
            text.setFillColor(sf::Color::Green);

            if(!board.check_board_is_valid()){
                text.setString("You lose!");
                text.setFillColor(sf::Color::Red);
            }
            
            text.setPosition(sf::Vector2f(140,100));
            sf::RenderWindow wn(sf::VideoMode({500u, 340u}), "Sudoku",sf::Style::Close );
            board.board[row][col] = 0;
            while(wn.isOpen()){
                wn.clear(sf::Color::White);
                wn.draw(text);

                while (const std::optional event = wn.pollEvent())
                {
                    if (event->is<sf::Event::Closed>()){
                        wn.close();
                    }
                }
                
                wn.display();
            }
        }
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>()){
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                col = (mouse_pos.x - 150) / 70;
                row = (mouse_pos.y - 10) / 70;
            }
            if (event->is<sf::Event::KeyPressed>()){
                sf::Keyboard::Key key = event->getIf<sf::Event::KeyPressed>()->code;
                edit_number(board, row, col, key, inaccessible_cells);
            }
        }
            window.display();
    }
}


