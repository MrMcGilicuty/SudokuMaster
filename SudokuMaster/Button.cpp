#include "Button.h"

void Button::addBackground(int width, int height, sf::Color color) {
    backWidth = width; // Initialize backWidth with the provided width
    backHeight = height; // Initialize backHeight with the provided height

    background.setPosition(newText.getPosition().x - abs(width - newText.getLocalBounds().width) / 2,
                           newText.getPosition().y - abs(height - newText.getLocalBounds().height) / 2);
    background.setFillColor(color);
    background.setScale(width, height);
}

void Button::addClickBackground(sf::Event& event, sf::RenderWindow& window, bool hold, int width, int height, sf::Color pressColor, sf::Color releaseColor) {
    clickBackground.setPosition(newText.getPosition().x - abs(newText.getLocalBounds().width - width) / 2,
                                newText.getPosition().y - abs(newText.getLocalBounds().height - height) / 2);
    clickBackground.setScale(width, height);

    if (event.type == event.MouseButtonPressed && isMouseOver(window, width, height)) {
        clickBackground.setFillColor(pressColor);
    }
    else if (event.type == event.MouseButtonReleased && !hold) {
        clickBackground.setFillColor(releaseColor);
    }
    else if (event.type == event.MouseButtonPressed && !isMouseOver(window, width, height)) {
        clickBackground.setFillColor(releaseColor);
    }
}

void Button::addClickBackground(sf::Event& event, sf::RenderWindow& window, bool hold, sf::Color pressColor, sf::Color releaseColor) {
    float width = backWidth;
    float height = backHeight;
    
    clickBackground.setPosition(newText.getPosition().x - abs(newText.getLocalBounds().width - width) / 2,
                                newText.getPosition().y - abs(newText.getLocalBounds().height - height) / 2);
    clickBackground.setScale(width, height);

    if (event.type == event.MouseButtonPressed && isMouseOver(window, width, height)) {
        clickBackground.setFillColor(pressColor);
    }
    else if (event.type == event.MouseButtonReleased && !hold) {
        clickBackground.setFillColor(releaseColor);
    }
    else if (event.type == event.MouseButtonPressed && !isMouseOver(window, width, height)) {
        clickBackground.setFillColor(releaseColor);
    }
}

bool Button::isMouseOver(sf::RenderWindow& window, float width, float height) {
    if (width == -1) {
        width = backWidth; // Use backWidth if width is not provided
    }
    if (height == -1) {
        height = backHeight; // Use backHeight if height is not provided
    }

    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    int posX = position.x;
    int posY = position.y;

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

    int posX = position.x;
    int posY = position.y;

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

void Button::drawBackground(sf::RenderWindow& window) {
    window.draw(background);
}

void Button::drawBackgrounds(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(clickBackground);
}