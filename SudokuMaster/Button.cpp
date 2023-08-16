#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f pos, int size, const std::string& fontFileLoc, bool sel, float ID, std::function<void(std::string)> clickCallback, sf::Color color)
    : EditNumber(pos, size, fontFileLoc, sel, ID, color), callback(clickCallback) {
    newText.setFont(newFont);
    newText.setPosition(pos);
    newText.setCharacterSize(size);
    newText.setFillColor(color);

    if (!newFont.loadFromFile(fontFileLoc)) {
        std::cout << "Error loading " << fontFileLoc << " file for custom font";
    }

    newText.setString(text);
    textWidth = newText.getLocalBounds().width;
    textHeight = newText.getGlobalBounds().height;
    selected = sel;
    CNID = ID;
}

void Button::addBackground(int width, int height, sf::Color color) {
    backWidth = width; // Initialize backWidth with the provided width
    backHeight = height; // Initialize backHeight with the provided height
    const float xPos = newText.getPosition().x - abs(width - textWidth) / 2;
    const float yPos = newText.getPosition().y - abs(height - textHeight * 2) / 2;

    background.setPosition(xPos, yPos);
    background.setFillColor(color);
    background.setSize(sf::Vector2f(width, height));
}

void Button::addClickBackground(sf::Event& event, sf::RenderWindow& window, bool hold, int width, int height, sf::Color pressColor, sf::Color releaseColor) {
    const float xPos = newText.getPosition().x - abs(width - textWidth) / 2;
    const float yPos = newText.getPosition().y - abs(height - textHeight * 2) / 2;

    clickBackground.setSize(sf::Vector2f(width, height));
    clickBackground.setPosition(xPos, yPos);
    clickBackground.setFillColor(releaseColor);

    if (event.type == event.MouseButtonPressed && isMouseOver(window, width, height)) {
        clickBackground.setFillColor(pressColor);
        callback(Button::baseFile);
    }
    else if (event.type == event.MouseButtonReleased && !hold) {
        clickBackground.setFillColor(releaseColor);
    }
    else if (event.type == event.MouseButtonPressed && !isMouseOver(window, width, height)) {
        clickBackground.setFillColor(releaseColor);
    }
}

void Button::addClickBackground(sf::Event& event, sf::RenderWindow& window, bool hold, sf::Color pressColor, sf::Color releaseColor) {
    const float width = backWidth;
    const float height = backHeight;
    const float xPos = newText.getPosition().x - abs(width - textWidth) / 2;
    const float yPos = newText.getPosition().y - abs(height - textHeight * 2) / 2;

    clickBackground.setSize(sf::Vector2f(width, height));
    clickBackground.setPosition(xPos, yPos);
    clickBackground.setFillColor(releaseColor);
    clickBackground.setOutlineThickness(3.0f);
    clickBackground.setOutlineColor(sf::Color::Black);


    if (event.type == event.MouseButtonPressed && isMouseOver(window, width, height)) {
        clickBackground.setFillColor(pressColor);
        callback(Button::baseFile);
    }
    else if (event.type == event.MouseButtonReleased && !hold) {
        clickBackground.setFillColor(releaseColor);
    }
    else if (event.type == event.MouseButtonPressed && !isMouseOver(window, width, height)) {
        clickBackground.setFillColor(releaseColor);
    }
}

bool Button::isMouseOver(sf::RenderWindow& window, float width, float height) {
    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    int posX = clickBackground.getPosition().x;
    int posY = clickBackground.getPosition().y;

    float endPosX = posX + width;
    float endPosY = posY + height;

    if (mouse.x > posX && mouse.x < endPosX && mouse.y > posY && mouse.y < endPosY) {
        select();
        return true;
    }
    else {
        deselect();
        return false;
    }
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    float width = backWidth;
    float height = backHeight;

    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    int posX = clickBackground.getPosition().x;
    int posY = clickBackground.getPosition().y;

    float endPosX = posX + width;
    float endPosY = posY + height;

    if (mouse.x > posX && mouse.x < endPosX && mouse.y > posY && mouse.y < endPosY) {
        select();
        return true;
    }
    else {
        deselect();
        return false;
    }
}

void Button::drawBack(sf::RenderWindow& window) {
    drawShape(window, background);
    drawShape(window, clickBackground);
}