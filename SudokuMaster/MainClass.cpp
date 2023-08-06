#include <SFML/Graphics.hpp>



int main()
{
    const sf::Vector2u window_size{2560, 1440};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Sudoku", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    const int gridSizeY = 3;
    const float cellHeight = window_size.y / (float)gridSizeY; // Length of 1 large cell off the 3x3 board
    const float dif = window_size.x - window_size.y; // Difference between the width and height of the screen
    const int wrap = 10; // The space pillow in-between each cellNum (in pixels)
    sf::RectangleShape boardV;
    sf::RectangleShape boardH;
    sf::RectangleShape boardEdge;
    // Shapes for side bars
    sf::RectangleShape barLeft;
    sf::RectangleShape barRight;

    // Draws board
    // Horizontal lines
    boardH.setSize(sf::Vector2f(window_size.x + 5, cellHeight));
    boardH.setOutlineThickness(5.0f);
    boardH.setFillColor(sf::Color::Transparent);
    boardH.setOutlineColor(sf::Color::Black);
    boardH.setPosition(sf::Vector2f(0, cellHeight));

    // Vertical lines
    boardV.setSize(sf::Vector2f(cellHeight, window_size.x + 5));
    boardV.setOutlineThickness(5.0f);
    boardV.setFillColor(sf::Color::Transparent);
    boardV.setOutlineColor(sf::Color::Black);
    boardV.setPosition(sf::Vector2f(dif / 2 + cellHeight, 0));
    
    // Board Edge
    boardEdge.setSize(sf::Vector2f(window_size.y - 10, window_size.y - 10));
    boardEdge.setOutlineThickness(5.0f);
    boardEdge.setFillColor(sf::Color::Transparent);
    boardEdge.setOutlineColor(sf::Color::Black);
    boardEdge.setPosition(dif / 2 + 5, 5);

    // Draws bars
    barLeft.setSize(sf::Vector2f(dif / 2, window_size.y));
    barLeft.setFillColor(sf::Color(0xEFEFEFFF));
    barLeft.setPosition(0,0);
    barRight.setSize(sf::Vector2f(dif / 2, window_size.y));
    barRight.setFillColor(sf::Color(0xEFEFEFFF));
    barRight.setPosition(window_size.y + dif / 2, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear(sf::Color(0xEFEFEFFF));
        // Board Prereqs:
        window.draw(boardH);
        window.draw(boardV);
        window.draw(boardEdge);
        window.draw(barLeft);
        window.draw(barRight);
        // Loops for drawing the smaller cells
        for (int x = 0; x < 9; ++x){
            for (int y = 0; y < 9; ++y) {
                sf::RectangleShape cellNum;
                const float cellNumWidth = cellHeight / 3 - (float)wrap;
                cellNum.setFillColor(sf::Color(0x9F9F9F99));
                cellNum.setSize(sf::Vector2f(cellNumWidth, cellNumWidth));
                cellNum.setPosition(x * (cellNumWidth + (float)wrap) + dif / 2 + (float)wrap, y * (cellNumWidth + (float)wrap) + (float)wrap);
                window.draw(cellNum);
            }
        }
        window.display();
    }

    return 0;
}