#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "colors.h"

class Box : public Colors
{
private:
	sf::RectangleShape rectangle;
	sf::RectangleShape line;
	sf::Font font;
	sf::Text text;
	std::string labelToDisplay;
	sf::Color pressedColor;
	bool autoAdjust, biselEnable, hoverSelect, biselPressed;
	float labelWidth();
	int characterLimit();
	void adjustText();
	void drawBisel(sf::RenderWindow& window);

public:
	Box();
	~Box();
	float x, y, xSize, ySize;
	std::string label;
	void press();
	void release();
	void setPressedColor(int red, int green, int blue);
	void button(std::string thisLabel);
	void inputField(std::string thisLabel);
	void draw(sf::RenderWindow& window);

};

