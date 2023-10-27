#pragma once
#include <SFML/Graphics.hpp>

class Box
{
private:
	sf::RectangleShape rectangle;
	sf::RectangleShape line;
	sf::Color filler();

public:
	Box();
	~Box();
	float x, y, xSize, ySize;
	int type;
	void draw(sf::RenderWindow& window);
};

