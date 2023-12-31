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
	static const int fontXsize = 8;
	static const int fontYsize = 15;

	sf::RectangleShape rectangle;
	sf::RectangleShape line;
	sf::Font font;
	sf::Text text;
	std::string labelToDisplay, cursor;
	sf::Color pressedColor;

	bool biselEnable, textWrap ,biselPressed, highlightOnHover, isFilled, forceWhiteText, shadowEnable;
	
	int characterLimit();
	void adjustText();
	void adjustTextWrap(sf::RenderWindow& window, std::string toPrint);
	void drawBisel(sf::RenderWindow& window);

public:
	Box();
	~Box();
	float x, y, xSize, ySize;
	bool autoAdjust;
	std::string label;
	bool isTouching(UserInteraction& User);
	bool isPressed();
	void press();
	void release();
	void highlight();
	float labelWidth();
	void setPressedColor(int red, int green, int blue);
	void setPressedColor(sf::Color thisColor);
	void nextTo(Box& thisBox);
	void forceWhite();
	void forceShadow();
	void button(std::string thisLabel);
	void textField(Box& thisBox, float adjustY, UserInteraction& User);
	void textLabel(std::string thisLabel);
	void menuItem(std::string thisLabel);
	void draw(sf::RenderWindow& window);

};

