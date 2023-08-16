#include "TextWizard.h"
#include <iostream>

TextWizard::TextWizard(sf::Vector2f pos, int size, const std::string& text, const std::string& fontFileLoc, sf::Color color) {
    newText.setPosition(pos);
    newText.setCharacterSize(size);
    newText.setString(text);
    newText.setFillColor(color);

    if (!newFont.loadFromFile(fontFileLoc)) {
        std::cout << "Error loading " << fontFileLoc << " file for custom font";
    }

    newText.setFont(newFont);
    textWidth = newText.getLocalBounds().width;
    textHeight = newText.getLocalBounds().height;
    position = pos;
}

void TextWizard::centerText(float width) {
    textWidth = width;
    sf::Vector2f text = sf::Vector2f(newText.getLocalBounds().width, newText.getLocalBounds().width);
    newText.setPosition((width - text.x) / 2 + position.x, position.y);
}

void TextWizard::setString(std::string string) {
    newText.setString(string);
}

void TextWizard::highlightText(sf::Color color) {
    highlight = true;
    highlightShape.setPosition(newText.getPosition().x + 4, newText.getPosition().y + 12);
    highlightShape.setFillColor(color);
    highlightShape.setSize(sf::Vector2f(newText.getLocalBounds().width + 6, newText.getLocalBounds().height));
}

void TextWizard::drawTo(sf::RenderWindow& window) {
    if (highlight) {
        window.draw(highlightShape);
    }
    window.draw(newText);
}

sf::Vector2f TextWizard::getPosition() {
    return newText.getPosition();
}

float TextWizard::getHeight() {
    return newText.getLocalBounds().height;
}

float TextWizard::getWidth() {
    return newText.getLocalBounds().width;
}