#include <SFML/Graphics.hpp>

int main()
{
    const sf::Vector2u window_size{2560, 1440};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Sudoku", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    const int gridSizeY = 3;
    const float cellHeight = window_size.y / (float)gridSizeY;
    const float dif = window_size.x - window_size.y;

    sf::RectangleShape boardV;
    sf::RectangleShape boardH;
    // Shapes for side bars
    sf::RectangleShape barLeft;
    sf::RectangleShape barRight;

    // Draws board
    // Horizontal lines
    boardH.setSize(sf::Vector2f(window_size.x + 20, cellHeight));
    boardH.setOutlineThickness(10.0f);
    boardH.setFillColor(sf::Color::Transparent);
    boardH.setOutlineColor(sf::Color::Black);
    boardH.setPosition(sf::Vector2f(0, cellHeight));

    // Vertical lines
    boardV.setSize(sf::Vector2f(cellHeight, window_size.x + 20));
    boardV.setOutlineThickness(10.0f);
    boardV.setFillColor(sf::Color::Transparent);
    boardV.setOutlineColor(sf::Color::Black);
    boardV.setPosition(sf::Vector2f(dif / 2 + cellHeight, 0));

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
        // Draw your content here
        window.draw(boardH);
        window.draw(boardV);
        window.draw(barLeft);
        window.draw(barRight);
        window.display();
    }

    return 0;
}