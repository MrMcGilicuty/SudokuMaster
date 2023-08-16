#pragma once
#include "EditNumber.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public EditNumber {
public:

	// Setting Constructor values for derived class
	Button(sf::Vector2f pos, int size, const std::string& fontFileLoc, bool sel, float ID, std::function<void(std::string)> clickCallback, sf::Color color = sf::Color::Black);

	/*
	* Adds a background with a color; the default color is white
	* 
	* \param width The width in pixels your background should be, centered on the middle of the text obejct.
	* \param height The height in pixels your background should be, centered on the middle of the text obejct.
	* 
	 */
	void addBackground(int width, int height, sf::Color color = sf::Color::White);

	/*
	* Adds an accent color with a bounding box when you click the button.
	* The default width and height is the selection for the background if you've made one.
	* 
	* \param event Refrences the event type
	* \param window Needed to check if the mouse is clicking on the background
	* \param hold Toggle whether the pressed Color should stay there until something else is clicked, or just flash
	* \param width Width of the box centered about the text
	* \param height Height of the box centered about the text
	* \param pressColor The color of the button when pressed
	* \param releaseColor The color of the button when released, or, if hold is true, the color of the button when clicked off
	* 
	*/
	void addClickBackground(sf::Event& event, sf::RenderWindow& window, bool hold, int width, int height, sf::Color pressColor = sf::Color::Black, sf::Color releaseColor = sf::Color::White);

	/*
	* Adds an accent color when you click the button.
	* The default width and height is the selection for the background if you've made one. 
	* |||||You MUST have called the addBackground() method before using this method.|||||
	*
	* \param event Refrences the event type
	* \param window Needed to check if the mouse is clicking on the background
	* \param hold Toggle whether the pressed Color should stay there until something else is clicked, or just flash
	* \param pressColor The color of the button when pressed
	* \param releaseColor The color of the button when released, or, if hold is true, the color of the button when clicked off
	*
	*/
	void addClickBackground(sf::Event& event, sf::RenderWindow& window, bool hold, sf::Color pressColor, sf::Color releaseColor);

	/* 
	* Returns True if the mouse is over the original object location.
	* 
	* \param width How wide the bounding box of the button is
	* \param height How tall the bounding box of the button is
	* 
	 */
	bool isMouseOver(sf::RenderWindow& window, float width, float height);

	/*
	  
	  Returns True if the mouse is over the background object location.
	  The default width and height is the selection for the background.
	  
	 */
	bool isMouseOver(sf::RenderWindow& window);

	// Draws the backgrounds
	void drawBack(sf::RenderWindow& window);

	std::string baseFile = "";
private:
	std::function<void(std::string)> callback; // Callback function

	// Initialization of values
	sf::RectangleShape background;
	sf::RectangleShape clickBackground;
	float backWidth = 0;
	float backHeight = 0;
	float CNID = 1.01;
};