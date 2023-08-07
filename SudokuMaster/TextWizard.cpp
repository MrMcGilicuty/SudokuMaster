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
    centered = true;
    textWidth = width;
    sf::Vector2f text = sf::Vector2f(newText.getLocalBounds().width, newText.getLocalBounds().width);
    newText.setPosition((width - text.x) / 2 + position.x, position.y);
}

void TextWizard::highlightText(sf::Color color) {
    highlight = true;
    highlightShape.setPosition(newText.getPosition());
    highlightShape.setFillColor(color);
    highlightShape.setSize(sf::Vector2f(newText.getLocalBounds().width, newText.getLocalBounds().height));
}

void TextWizard::drawTo(sf::RenderWindow& window) {
    if (highlight) {
        window.draw(highlightShape);
    }
    window.draw(newText);
}

std::string TextWizard::getText() {
    return newText.getString();
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