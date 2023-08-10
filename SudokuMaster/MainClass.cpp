#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "TextWizard.h"
#include "EditNumber.h"

void dispose(std::vector<std::vector<EditNumber*>> numberCells, sf::RenderWindow &window) {
    // Clean up memory before exiting
    for (std::vector<EditNumber*>& row : numberCells) {
        for (EditNumber* cellTextNum : row) {
            delete cellTextNum; // Deallocate the object
        }
    }

    // Clear the numberCells vector
    numberCells.clear();
    window.close();
}

int main()
{
    const sf::Vector2u window_size{2560, 1440};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Sudoku", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    const int gridSizeY = 3;
    const float cellHeight = window_size.y / (float)gridSizeY; // Length of 1 large cell off the 3x3 board
    const float dif = window_size.x - window_size.y; // Difference between the width and height of the screen
    const float cellNumWidth = 155; // Size of each number cell
    const int wrap = (cellHeight / 3 - cellNumWidth); // The padding in-between each cellNum (in pixels)
    std::string mode = "Sandbox";

    sf::RectangleShape boardV;
    sf::RectangleShape boardH;
    sf::RectangleShape boardEdge;
    // Shapes for side bars
    sf::RectangleShape barLeft;
    sf::RectangleShape barRight;
    // Creating the vector to hold each CellTextNum 9x9 board
    std::vector<std::vector<EditNumber*>> numberCells;

    // Fonts:
    // 
    // data-latin.ttf
    // Caviar Dreams Bold.ttf
    //
    // Loading Title text
    TextWizard titleText(sf::Vector2f(0,20), 60, "Sudoku:", "resources/data-latin.ttf");
    titleText.centerText(dif/2);
   
    // Loading Title subtext
    TextWizard subText(sf::Vector2f(0, titleText.getHeight() + 50), 40, "Ultimate edition", "resources/data-latin.ttf");
    subText.centerText(dif / 2);

    TextWizard modeText(sf::Vector2f(dif / 2 + window_size.y, 20), 60, mode + " Mode", "resources/data-latin.ttf");
    modeText.centerText(dif / 2);

    // Draws board
    // Horizontal lines
    boardH.setSize(sf::Vector2f(window_size.y, cellHeight - (float)wrap));
    boardH.setOutlineThickness(wrap);
    boardH.setFillColor(sf::Color::Transparent);
    boardH.setOutlineColor(sf::Color::Black);
    boardH.setPosition(sf::Vector2f(dif / 2 + (float)wrap, cellHeight + (float)wrap));

    // Vertical lines
    boardV.setSize(sf::Vector2f(cellHeight - (float)wrap, window_size.x));
    boardV.setOutlineThickness(wrap);
    boardV.setFillColor(sf::Color::Transparent);
    boardV.setOutlineColor(sf::Color::Black);
    boardV.setPosition(sf::Vector2f(dif / 2 + cellHeight + (float)wrap, 0));
    
    // Board Edge
    boardEdge.setSize(sf::Vector2f(window_size.y - (float)wrap, window_size.y - (float)wrap * 1));
    boardEdge.setOutlineThickness(wrap);
    boardEdge.setFillColor(sf::Color::Transparent);
    boardEdge.setOutlineColor(sf::Color::Black);
    boardEdge.setPosition(dif / 2 + (float)wrap, (float)wrap);

    // Draws bars
    barLeft.setSize(sf::Vector2f(dif / 2, window_size.y));
    barLeft.setFillColor(sf::Color(0xEFEFEFFF));
    barLeft.setPosition(0,0);
    barRight.setSize(sf::Vector2f(dif / 2, window_size.y));
    barRight.setFillColor(sf::Color(0xEFEFEFFF));
    barRight.setPosition(window_size.y + dif / 2 + (float)wrap, 0);

    for (int x = 0; x < 9; ++x) {
        // Declare a new row for this x index
        std::vector<EditNumber*> row;
        for (int y = 0; y < 9; ++y) {

            // Make the new object for the pointer
            EditNumber* cellTextNum = new EditNumber(
                sf::Vector2f(x * (cellNumWidth + (float)wrap) + (dif / 2 + (float)wrap), y * (cellNumWidth + (float)wrap) + (float)wrap),
                100,
                "resources/data-latin.ttf",
                false,
                1.02f);
            // Add EditNumber to the row
            row.push_back(cellTextNum);
        }
        // Add the row to the numberCells vector
        numberCells.push_back(row);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                dispose(numberCells, window);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tilde) {
                dispose(numberCells, window);
            }
            else if (event.type == sf::Event::TextEntered) {
                for (std::vector<EditNumber*>& row : numberCells) {
                    for (EditNumber* cellTextNum : row) {

                        cellTextNum->typedOn(event);
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {

                for (std::vector<EditNumber*>& row : numberCells) {
                    for (EditNumber* cellTextNum : row) {
                        cellTextNum->deselect();
                        cellTextNum->showHitBox(false);
                        if (cellTextNum->isMouseOver(window, cellNumWidth)) {
                            cellTextNum->select();
                            cellTextNum->showHitBox(true, cellNumWidth);
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(0xEFEFEFFF));
        // Board Prereqs:
        window.draw(boardH);
        window.draw(boardV);
        window.draw(boardEdge);
        window.draw(barLeft);
        window.draw(barRight);
        modeText.drawTo(window);
        // Loop for drawing the smaller cells
        for (int x = 0; x < 9; ++x){
            for (int y = 0; y < 9; ++y) {
                sf::RectangleShape cellNum;
                cellNum.setFillColor(sf::Color(0xAFAFAF99));
                cellNum.setSize(sf::Vector2f(cellNumWidth, cellNumWidth));
                // Calculate position to account for the padding        \This is the origin/                                       \Also Origin/
                cellNum.setPosition(x * (cellNumWidth + (float)wrap) + (dif / 2 + (float)wrap), y * (cellNumWidth + (float)wrap) + (float)wrap);
                window.draw(cellNum);
            }
        }
        for (std::vector<EditNumber*>& row : numberCells) {
            for (EditNumber* cellTextNum : row) {
                // For every item in the vector draw to screen.
                cellTextNum->centerText(cellNumWidth);
                cellTextNum->drawTo(window);
                
            }
        }
        titleText.drawTo(window);
        subText.drawTo(window);
        window.display();
    }

    return 0;
}