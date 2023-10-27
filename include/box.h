#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Box
{
private:
	sf::RectangleShape rectangle;
	sf::RectangleShape line;
	sf::Font font;
	sf::Text text;
	int labelWitdh();
	int characterLimit();

public:
	Box();
	~Box();
	float x, y, xSize, ySize;
	int type;
	std::string label;
	void draw(sf::RenderWindow& window);
};

