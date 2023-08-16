#pragma once
#include <SFML/Graphics.hpp>

// Class for making Text really easy
class TextWizard
{
public:
	// Constructor for Text values
	TextWizard(sf::Vector2f pos, int size, const std::string& text, const std::string& fontFileLoc, sf::Color color = sf::Color::Black); 

	/* Centeres the text based on how wide the given area is
	 (Optional)*/
	void centerText(float width);

	/* Sets the background highlight color 
	(Optional)*/
	void highlightText(sf::Color color);

	/* Draws the Text to the given window (Required)

	 \param window sf::RenderWindow to render the object to
	 */
	void drawTo(sf::RenderWindow& window);
	// Sets the String
	void setString(std::string string);

	// Returns the position of the Text Object
	sf::Vector2f getPosition();
	// Returns the Height of the Text Object
	float getHeight();
	// Returns the Width of the Text Object
	float getWidth();

private:
	sf::Text newText;
	sf::Font newFont;
	sf::RectangleShape highlightShape;
	float textWidth = 0;
	float textHeight = 0;
	bool highlight = false;
	sf::Vector2f position;
};

