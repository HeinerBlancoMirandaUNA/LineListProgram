#include "box.h"

Box::Box() {
	rectangle.setSize(sf::Vector2f(20, 20));
	line.setSize(sf::Vector2f(1, 20));
	x = 0;
	y = 0;
	button("");
	font.loadFromFile("resources/LessPerfectDOSVGA.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	pressedColor = biselB;
	
}
Box::~Box() {

}

float Box::labelWidth() {
	return (static_cast<float>(label.length()) * 8) + 10;
}

int Box::characterLimit() {
	if (static_cast<int>(xSize) < 10) { return 0; }
	return static_cast<int>((xSize - 10) / 8);
}

void Box::nextTo(Box& thisBox) {
	x = thisBox.x + thisBox.xSize + 5;
	y = thisBox.y;
}

void Box::button(std::string thisLabel) {
	autoAdjust = true;
	biselEnable = true;
	biselPressed = false;
	highlightOnHover = false;
	label = thisLabel;
	xSize = labelWidth() + 25;
	ySize = 24;
}

void Box::textField(std::string thisLabel) {
	autoAdjust = false;
	biselEnable = true;
	biselPressed = true; 
	highlightOnHover = false;
	label = thisLabel;
	ySize = 24;
}

void Box::setPressedColor(int red, int green, int blue) {
	pressedColor = sf::Color(red, green, blue);
}

void Box::press() {
	biselPressed = true;
}

void Box::release() {
	biselPressed = false;
}

void Box::highlight() {
	highlightOnHover = true;
}

bool Box::isTouching(UserInteraction& User) {
	if ((User.x < x) or (User.y < y)) { return false; }
	if ((User.x > x + xSize) or (User.y > y + ySize)) { return false; }
	return true;
}

void Box::adjustText() {
	text.setPosition(x + 5, y);
	labelToDisplay = label;
	if (label.length() > characterLimit()) {
		if (characterLimit() < 1) { labelToDisplay = ""; return; }
		labelToDisplay = char(17) + (label.substr(label.length() + 1 - characterLimit(), label.length()));
	}
	else {
		if (!autoAdjust) { return; }
		float adjust = xSize - labelWidth();
		adjust = adjust / 2; // don't divide by 2 to adjust to the right
		adjust = adjust;
		text.move(std::round(adjust), 0);
	}
}

void Box::drawBisel(sf::RenderWindow& window) {

	sf::Color upperSide = biselA; 
	sf::Color lowerSide = biselD;
	sf::Color middleShadow = biselC;

	if (biselPressed) {
		upperSide = biselD;
		lowerSide = biselB;
		middleShadow = biselA;
	}

	line.setFillColor(lowerSide);
	line.setPosition(sf::Vector2f(x, (y + ySize) - 1));
	line.setSize(sf::Vector2f(xSize, 1)); window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize) - 1, y + 1));
	line.setSize(sf::Vector2f(1, ySize - 1)); window.draw(line);

	line.setFillColor(middleShadow);
	line.setPosition(sf::Vector2f(x + 1, (y + (ySize - 2))));
	line.setSize(sf::Vector2f(xSize - 2, 1)); window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize) - 2, y + 1));
	line.setSize(sf::Vector2f(1, ySize - 2)); window.draw(line);

	line.setFillColor(upperSide);
	line.setPosition(sf::Vector2f(x + 1, y + 1));
	line.setSize(sf::Vector2f(xSize - 2, 1)); window.draw(line);
	line.setSize(sf::Vector2f(1, ySize - 3)); window.draw(line);
	line.setPosition(sf::Vector2f(x, y));
	line.setSize(sf::Vector2f(xSize, 1)); window.draw(line);
	line.setSize(sf::Vector2f(1, ySize-1)); window.draw(line);

	if (!biselPressed) { return; }

	line.setFillColor(biselC);
	line.move(2, 2); 
	line.setSize(sf::Vector2f(1, ySize - 4)); window.draw(line);
	line.setSize(sf::Vector2f(xSize - 4, 1));	window.draw(line);

}

void Box::draw(sf::RenderWindow& window) {

	rectangle.setFillColor(biselB);
	if (biselPressed) { rectangle.setFillColor(pressedColor); }
	rectangle.setPosition(sf::Vector2f(x, y));
	rectangle.setSize(sf::Vector2f(xSize, ySize));
	window.draw(rectangle);

	if (biselEnable) {
		drawBisel(window);
	}
	
	text.setFillColor(normalText);

	if (highlightOnHover) {
		text.setFillColor(selectedText);
		rectangle.setFillColor(selected);
		rectangle.setPosition(sf::Vector2f(x + 3, y + 3));
		rectangle.setSize(sf::Vector2f(xSize - 7, ySize - 7));
		window.draw(rectangle);
		highlightOnHover = false;
	}

	adjustText();
	if (biselPressed) { text.move(1,1); }
	text.setString(labelToDisplay); window.draw(text);
	
}

