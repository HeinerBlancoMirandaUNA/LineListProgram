#include "box.h"

Box::Box() {
	rectangle.setSize(sf::Vector2f(20, 20));
	line.setSize(sf::Vector2f(1, 20));
	x = 0;
	y = 0;
	xSize = 0;
	ySize = 0;
	type = 0;
	font.loadFromFile("resources/LessPerfectDOSVGA.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	label = "";
}
Box::~Box() {

}

int Box::labelWitdh() {
	return static_cast<unsigned int>((label.length() * 8) + 10);
}

int Box::characterLimit() {
	if (static_cast<int>(xSize) < 10) { return 0; }
	return static_cast<int>((xSize - 10) / 8);
}

void Box::draw(sf::RenderWindow& window) {

	sf::Color biselA(255, 255, 255);
	sf::Color biselB(195, 195, 195);
	sf::Color biselC(128, 128, 128);
	sf::Color biselD(0, 0, 0);
	sf::Color selected(0, 0, 130);

	rectangle.setFillColor(biselB);
	rectangle.setPosition(sf::Vector2f(x, y));
	rectangle.setSize(sf::Vector2f(xSize, ySize));
	window.draw(rectangle);

	line.setFillColor(biselD);
	line.setPosition(sf::Vector2f(x, (y + ySize) - 1));
	line.setSize(sf::Vector2f(xSize, 1)); window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize) - 1, y + 1));
	line.setSize(sf::Vector2f(1, ySize - 1)); window.draw(line);

	line.setFillColor(biselC);
	line.setPosition(sf::Vector2f(x + 1, (y + (ySize-2))));
	line.setSize(sf::Vector2f(xSize - 2, 1)); window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize) - 2, y + 1));
	line.setSize(sf::Vector2f(1, ySize - 2)); window.draw(line);

	line.setFillColor(biselA);
	line.setPosition(sf::Vector2f(x + 1, y + 1));
	line.setSize(sf::Vector2f(xSize-2, 1)); window.draw(line);
	line.setSize(sf::Vector2f(1, ySize - 3)); window.draw(line);

	std::string labelToDisplay = label;
	if (label.length() > characterLimit()) {
		labelToDisplay = label.substr(label.length()-characterLimit(), label.length());
	}
	text.setFillColor(sf::Color::Black);
	text.setPosition(x + 5, y);
	text.setString(labelToDisplay); window.draw(text);
	
}

