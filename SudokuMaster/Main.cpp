#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include "TextWizard.h"
#include "EditNumber.h"
#include "Button.h"
#include "SudokuDLXMatrix.h"
namespace fs = std::filesystem;
#define COMMENT '#' // This defines the comment symbol used in the custom level files can be anything besides numbers, commas, or spaces
#define SOLUTION '=' // This defines the Solution symbol used in the custom level files that tells the reader to start loading the solution

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

std::vector<std::vector<int>> loadSudokuFile(std::string fileName) {
    bool commentStart = false; // Bool for opening/closing comments
    std::ifstream sudokuFile(fileName); // Loads the file
    // If the file doesn't load it notifies you
    if (!sudokuFile.is_open()) {
        std::cout << "Failed to open the file!" << std::endl;
    }

    char ch;
    std::vector<std::vector<int>> boardNums; // The Vector that will hold the starting board position
    std::vector<int> row; // Row vector
    int i(0); // Index
    // Cycles through every character in the file printing out every number
    while (sudokuFile.get(ch)) {
        if (ch == COMMENT && !commentStart)
            commentStart = true;
        else if (ch == COMMENT && commentStart) 
            commentStart = false;
        
        // If you are not in a comment then check for numbers
        if (!commentStart) {
            if (ch >= '0' && ch <= '9') {
                // Subtract the unicode value to get the actual value as an integer
                int charNum = ch - '0';
                // Every 9 numbers push back 1 row
                if (i % 9 != 0 || i == 0) {
                    row.push_back(charNum);
                    i++;
                }
                else {
                    std::cout << std::endl;
                    boardNums.push_back(row);
                    row.clear();
                    row.push_back(charNum);
                    i++;
                }
                std::cout << ch;
            }
            
        }
    }
    std::cout << std::endl;
    boardNums.push_back(row);
    sudokuFile.close();
    return boardNums;
}

std::vector<std::vector<int>> loadSudokuSolution(std::string fileName) {
    bool commentStart = false; // Bool for opening/closing comments
    bool solutionStart = false; // Bool for starting the solution
    std::ifstream sudokuFile(fileName); // Loads the file
    // If the file doesn't load it notifies you
    if (!sudokuFile.is_open()) {
        std::cout << "Failed to open the file!" << std::endl;
    }

    char ch;
    std::vector<std::vector<int>> solutionNums; // The Vector that will hold the starting board position
    std::vector<int> row; // Row vector
    int i(0); // Index
    // Cycles through every character in the file printing out every number
    while (sudokuFile.get(ch)) {
        // Starts the comment
        if (ch == COMMENT && !commentStart) 
            commentStart = true;
        // Ends the comment
        else if (ch == COMMENT && commentStart) 
            commentStart = false;
        // Starts Solution
        if (ch == SOLUTION && !commentStart)
            solutionStart = true;
        // If you are not in a comment and you have reached the Solution Symbol then check for numbers
        if (solutionStart && !commentStart) {
            if (ch >= '0' && ch <= '9') {
                // If there is a zero in the solution it will Error, and the solution will be scrapped
                if (ch == '0') {
                    std::cout << "Error: No Zeros are alloud in the solution.\n";
                    solutionStart = false;
                    break;
                }
                // Subtract the unicode value to get the actual value as an integer
                int charNum = ch - '0';
                // Every 9 numbers push back 1 row
                if (i % 9 != 0 || i == 0) {
                    row.push_back(charNum);
                    i++;
                }
                else {
                    std::cout << std::endl;
                    solutionNums.push_back(row);
                    row.clear();
                    row.push_back(charNum);
                    i++;
                }
                std::cout << ch;
            }

        }
    }
    if (!solutionStart) {
        std::cout << "No Solution avaliable.\n";
    }
    std::cout << std::endl;
    solutionNums.push_back(row);
    sudokuFile.close();
    return solutionNums;
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
    //Map for Fonts
    std::map<int, std::string> fonts {
        { 1, "resources/data-latin.ttf" },
        { 2, "resources/Caviar Dreams Bold.ttf" },
    };
    // Path of the level directory
    std::string levelPath = "levels";
    

    // Loading Title text
    TextWizard titleText(sf::Vector2f(0,20), 60, "Sudoku:", fonts[1]);
    titleText.centerText(dif/2);
   
    // Loading Title subtext
    TextWizard subText(sf::Vector2f(0, titleText.getHeight() + 50), 40, "Ultimate edition", fonts[1]);
    subText.centerText(dif / 2);

    // Loading Mode text
    TextWizard modeText(sf::Vector2f(dif / 2 + window_size.y, 20), 60, mode + " Mode", fonts[1]);
    modeText.centerText(dif / 2);

    // Loading Level text
    TextWizard levelText(sf::Vector2f(dif / 2 + window_size.y, 180), 60, "Levels:", fonts[1]);
    levelText.centerText(dif / 2);

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

    int id(0);
    for (int x = 0; x < 9; ++x) {
        // Declare a new row for this x index
        std::vector<EditNumber*> row;
        for (int y = 0; y < 9; ++y) {
            
            // Make the new object for the pointer
            EditNumber* cellTextNum = new EditNumber(
                sf::Vector2f(x * (cellNumWidth + (float)wrap) + (dif / 2 + (float)wrap), y * (cellNumWidth + (float)wrap) + (float)wrap),
                100,
                fonts[2],
                false,
                id);
            // Add EditNumber to the row
            row.push_back(cellTextNum);
            ++id;
        }
        // Add the row to the numberCells vector
        numberCells.push_back(row);
    }

    // Lambda for checking the cells with the solution in the file
    auto checkCells = [&numberCells](std::string fileName) {
        std::vector<std::vector<int>> solutionVector = loadSudokuSolution(fileName);
        std::vector<std::vector<int>> boardVector = loadSudokuFile(fileName);
        int x(0);
        int y(0);
        for (std::vector<EditNumber*>& row : numberCells) {
            y = 0;
            for (EditNumber* cellTextNum : row) {
                int cell = cellTextNum->getNumber();
                int solCell = solutionVector[y][x];
                int presetCell = boardVector[y][x];

                if (presetCell != solCell) {

                    if (cell == solCell) {
                        cellTextNum->setColor(sf::Color(0x20D820FF));
                    }
                    else
                    {
                        if (cell != 0)
                            cellTextNum->setColor(sf::Color::Red);
                    }
                }
                y++;
            }
            x++;
        }
    };
    Button checkSol(sf::Vector2f(0, 1210), 60, fonts[1], false, 4.0f, checkCells);

    // Lambda for Loading the cells in when you press a level button
    auto loadCells = [&numberCells, &mode, &checkSol](std::string fileName) {
        std::vector<std::vector<int>> boardVector = loadSudokuFile(fileName);
        checkSol.baseFile = fileName; // Setting the check button's file
        mode = "Preset";
        int x(0);
        int y(0);
        for (std::vector<EditNumber*>& row : numberCells) {
            y = 0;
            for (EditNumber* cellTextNum : row) {
                if (boardVector[y][x] == 0) {
                    cellTextNum->allowInput();
                    cellTextNum->setString("", sf::Color(0xE9EB76FF));
                }
                else
                {
                    cellTextNum->blockInput(); // Turns off user input if it is generated by the map
                    cellTextNum->setString(std::to_string(boardVector[y][x]), sf::Color::Black);
                }
                y++;
            }
            x++;
        }
    };
    
    SudokuDLXMatrix matrixMaker;

    // For debugging
    /*std::vector<std::vector<bool>> boolMatrix = matrixMaker.createBoolMatrix();
    std::cout << "\n";
    // For printing out the boolMatrix
    /*for (const auto& rows : boolMatrix) {
        for (const auto& num : rows) {
            num ? std::cout << num : std::cout << "_";
        }
        std::cout << "\n";
    }*/

    matrixMaker.solve();

    // Draw Loop
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
        // Draws the green button
        checkSol.setString("Check Solution");
        checkSol.blockInput();

        checkSol.centerText(dif / 2);
        checkSol.addBackground(dif / 2 - 100, 100);
        checkSol.addClickBackground(event, window, false, sf::Color(0x109830FF), sf::Color(0x20D820FF));
        checkSol.drawBack(window);
        checkSol.drawTo(window);

        modeText.setString(mode + " Mode");
        modeText.drawTo(window);
        levelText.drawTo(window);
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
        // Loop for drawing all the level files
        int i(0);
        for (const auto& entry : fs::directory_iterator(levelPath)) {
            Button levelText(sf::Vector2f(dif / 2 + window_size.y, 320 + (80 * i)), 40, fonts[1], false, 2.1f, loadCells);

            levelText.baseFile = entry.path().string(); // Sets the filename

            // Removes the path and suffix from the text to just get the name of the file
            std::string finalString = entry.path().string();
            std::string path = "levels/";
            std::string suffix = ".txt";
            finalString.erase(0, path.length());

            std::string::size_type j = finalString.find(suffix);
            if (j != std::string::npos)
                finalString.erase(j, suffix.length());

            levelText.setString(finalString);
            levelText.centerText(dif / 2);
            levelText.addBackground(dif / 2 - 50, 50, sf::Color(0xAFAFAF99));

            // This does all of the clicking detection and swapping colors by itself.
            levelText.addClickBackground(event, window, false, sf::Color(0x7F7F7Fff), sf::Color(0xAFAFAF99));

            
            levelText.drawBack(window);
            levelText.drawTo(window);
            ++i;
        }

        window.display();
    }

    return 0;
}