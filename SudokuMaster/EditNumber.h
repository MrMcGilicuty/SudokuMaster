#pragma once
#include <SFML/Graphics.hpp>

class EditNumber
{
public:
	// Default constructors are for idiots
	//EditNumber();

	// Parameterized constructor
	EditNumber(sf::Vector2f pos, int size, const std::string& fontFileLoc, bool sel, float ID, sf::Color color = sf::Color::Black);

	/* Centeres the text based on how wide the given area is
	(Optional)*/
	void centerText(float width);

	/* Sets the background highlight on
	(Optional)*/
	void showHitBox(bool show);

	/* Sets the background highlight on and what size it should be
	(Optional)*/
	void showHitBox(bool show, float length);

	// Draws the Text to the given window (Required)
	void drawTo(sf::RenderWindow& window);
	// Draws a shape that you pass though
	void drawShape(sf::RenderWindow& window, sf::Drawable& shape);

	/* Returns True if the mouse is over the original object location
	 \param length How large the Square bounding box of the text about the origin
	 */
	bool isMouseOver(sf::RenderWindow& window, float length);
	/* Returns True if the mouse is over the original object location
	 \param width How wide the bounding box of the button is
	 \param height How tall the bounding box of the button is
	 */
	bool isMouseOver(sf::RenderWindow& window, float width, float height);
	// Returns True if the mouse is over the original text object location
	bool isMouseOver(sf::RenderWindow& window);
	// Sets the current Text Object as selected
	void select();
	// Sets the current Text Object as not selected
	void deselect();
	// Returns the Number of the Text Object
	int getNumber();
	// Sets the String to the passed string
	void setString(std::string string);
	// This is what notifies when you actually type something
	void typedOn(sf::Event& event);
	// Returns the ID of this Number Object
	float getID();

protected:
	// Returns the position of the Text Object
	sf::Vector2f getPosition();
	// Returns the Height of the Text Object
	float getHeight();
	// Returns the Width of the Text Object
	float getWidth();

	// Input logic to see if you delete the number or what you type
	void inputLogic(int charTyped);

	float CNID = 1.01;
	std::string text = "";
	sf::Text newText;
	sf::Font newFont;
	bool selected = false;
	float textWidth = 0;
	float textHeight = 0;
private:
	sf::RectangleShape highlightShape;
	bool highlight = false;
	sf::Vector2f position;
};

