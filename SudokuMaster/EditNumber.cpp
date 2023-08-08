#include "EditNumber.h"
#include <iostream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

EditNumber::EditNumber() : EditNumber(sf::Vector2f(0,0), 100, "resources/data-latin.ttf", false, 1.01f, sf::Color::Black) {
    
}

EditNumber::EditNumber(sf::Vector2f pos, int size, const std::string& fontFileLoc, bool sel, float ID, sf::Color color) {
    newText.setPosition(pos);
    newText.setCharacterSize(size);
    newText.setFillColor(color);

    if (!newFont.loadFromFile(fontFileLoc)) {
        std::cout << "Error loading " << fontFileLoc << " file for custom font";
    }

    newText.setFont(newFont);
    newText.setString(text);
    textWidth = newText.getLocalBounds().width;
    textHeight = newText.getLocalBounds().height;
    selected = sel;
    position = pos;
    CNID = ID;
}

void EditNumber::centerText(float width) {
    textWidth = width;
    sf::Vector2f text = sf::Vector2f(newText.getLocalBounds().width, newText.getLocalBounds().width);
    newText.setPosition((width - text.x) / 2 + position.x, position.y);
}

void EditNumber::highlightText(sf::Color color) {
    highlight = true;
    highlightShape.setPosition(newText.getPosition().x + 4, newText.getPosition().y + 12);
    highlightShape.setFillColor(color);
    highlightShape.setSize(sf::Vector2f(newText.getLocalBounds().width + 6, newText.getLocalBounds().height));
}

void EditNumber::drawTo(sf::RenderWindow& window) {
    if (highlight) {
        window.draw(highlightShape);
    }
    //window.draw(newText);
}

void EditNumber::typedOn(sf::Event &event) {
    if (selected) {
        int charTyped = event.text.unicode;
        if (charTyped > 48 && charTyped < 58 || charTyped == DELETE_KEY || charTyped == ENTER_KEY || charTyped == ESCAPE_KEY) {
            if (text.length() < 1) {
                inputLogic(charTyped);
            }
            else if (charTyped == DELETE_KEY) {
                text = "";
                newText.setString(text);
                
            }
        }
    }
}

int EditNumber::getNumber() {
    std::string numString= newText.getString();
    return std::stoi(numString);
}

sf::Vector2f EditNumber::getPosition() {
    return newText.getPosition();
}

float EditNumber::getHeight() {
    return newText.getLocalBounds().height;
}

float EditNumber::getWidth() {
    return newText.getLocalBounds().width;
}

float EditNumber::getID() {
    return CNID;
}

void EditNumber::inputLogic(int charTyped) {
    if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY) {
        text += std::string(1, charTyped);
        newText.setString(text);
    }
    else if (charTyped == ESCAPE_KEY) {
        selected = false;
    }
}