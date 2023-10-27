#include "box.h"

Box::Box() {
	rectangle.setSize(sf::Vector2f(20, 20));
	line.setSize(sf::Vector2f(1, 20));
	x = 0;
	y = 0;
	xSize = 0;
	ySize = 0;
	type = 0;
}
Box::~Box() {

}

sf::Color Box::filler() {
	if (type == 0) {
		return sf::Color(195, 195, 195);
	}

	return sf::Color(0, 0, 0);

}

void Box::draw(sf::RenderWindow& window) {

	sf::Color biselA(255,255,255);
	sf::Color biselB(195, 195, 195);
	sf::Color biselC(128, 128, 128);
	sf::Color biselD(0, 0, 0);
	sf::Color selected(0, 0, 130);

	rectangle.setFillColor(biselB);
	rectangle.setPosition(sf::Vector2f(x,y));
	rectangle.setSize(sf::Vector2f(xSize, ySize));
	window.draw(rectangle);

	line.setFillColor(biselD);
	line.setPosition(sf::Vector2f(x, (y + ySize)-1));
	line.setSize(sf::Vector2f(xSize, 1));
	window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize)-1, y+1));
	line.setSize(sf::Vector2f(1, ySize-1));
	window.draw(line);

	line.setFillColor(biselC);
	xSize--; ySize--;
	line.setPosition(sf::Vector2f(x+1, (y + ySize) - 1));
	line.setSize(sf::Vector2f(xSize-1, 1));
	window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize) - 1, y + 1));
	line.setSize(sf::Vector2f(1, ySize - 1));
	window.draw(line);

	line.setFillColor(biselA);
	xSize--; ySize--;
	line.setPosition(sf::Vector2f(x+1, y+1));
	line.setSize(sf::Vector2f(xSize, 1));
	window.draw(line);
	line.setSize(sf::Vector2f(1, ySize - 1));
	window.draw(line);

}

