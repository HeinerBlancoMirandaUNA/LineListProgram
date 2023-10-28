#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "colors.h"
#include "user_interaction.h"
#include "iostream"

class Box : public Colors
{
private:
	sf::RectangleShape rectangle;
	sf::RectangleShape line;
	sf::Font font;
	sf::Text text;
	std::string labelToDisplay;
	sf::Color pressedColor;
	bool autoAdjust, biselEnable, highlightOnHover, biselPressed;
	float labelWidth();
	int characterLimit();
	void adjustText();
	void drawBisel(sf::RenderWindow& window);

public:
	Box();
	~Box();
	float x, y, xSize, ySize;
	std::string label;
	bool isTouching(UserInteraction& User);
	void press();
	void release();
	void highlight();
	void setPressedColor(int red, int green, int blue);
	void nextTo (Box& thisBox);
	void button(std::string thisLabel);
	void textField(std::string thisLabel);
	void draw(sf::RenderWindow& window);

};

