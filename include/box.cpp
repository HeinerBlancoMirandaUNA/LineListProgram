#include "box.h"

Box::Box() {
	rectangle.setSize(sf::Vector2f(20, 20));
	line.setSize(sf::Vector2f(1, 20));
	x = 0;
	y = 0;
	button("");
	cursor = "";
	//WARNING: Do not instanciate too many boxes, as each time one get's created, cpu time gets wasted loading the font
	font.loadFromFile("resources/LessPerfectDOSVGA.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	pressedColor = biselB;
	forceWhiteText = false;
	std::cout << ">>> New Box Created" << std::endl;
	
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

void Box::forceWhite() {
	forceWhiteText = true;
}

void Box::button(std::string thisLabel) {
	isFilled = true;
	autoAdjust = true;
	biselEnable = true;
	biselPressed = false;
	highlightOnHover = false;
	label = thisLabel;
	xSize = labelWidth() + 25;
	ySize = 24;
}

void Box::textField(Box& thisBox, float adjustY, UserInteraction& User) {
	setPressedColor(inputBox);
	isFilled = true;
	autoAdjust = false;
	biselEnable = true;
	biselPressed = true;
	highlightOnHover = false;

	bool inputAllowed = User.key > 0 && User.key != 8 && User.key != 13;

	if (inputAllowed) {
		label = label + User.key;
	}
	if (User.key == 8 && label.length() > 0) {
		label.pop_back();
	}
	cursor = char(22);	if (User.timer % 1000 < 500) { cursor = " "; }

	float cutout = 15;

	x = thisBox.x + cutout; 
	xSize = thisBox.xSize - (2*cutout);
	ySize = 24;
	y = (thisBox.y + thisBox.ySize) - adjustY;
}

void Box::menuItem(std::string thisLabel) {
	isFilled = false;
	autoAdjust = false;
	biselEnable = false;
	biselPressed = false;
	highlightOnHover = false;
	label = thisLabel;
	ySize = 23;

}

void Box::setPressedColor(int red, int green, int blue) {
	pressedColor = sf::Color(red, green, blue);
}

void Box::setPressedColor(sf::Color thisColor) {
	pressedColor = thisColor;
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

bool Box::isPressed() {
	return biselPressed;
}

void Box::adjustText() {
	text.setPosition(x + 5, y);
	labelToDisplay = label;
	int length = static_cast<int>(label.length() + cursor.length());
	if (length > characterLimit()) {
		if (characterLimit() < 1) { labelToDisplay = ""; return; }
		labelToDisplay = char(17) + (label.substr(length + 1 - characterLimit(), length));
	}
	else {
		if (!autoAdjust) { return; }
		float adjust = xSize - labelWidth();
		adjust = adjust / 2;
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
		
		line.setFillColor(biselC);
		line.setPosition(sf::Vector2f(x+2, y+2));
		line.setSize(sf::Vector2f(1, ySize - 4)); window.draw(line);
		line.setSize(sf::Vector2f(xSize - 4, 1));	window.draw(line);
	}

	line.setFillColor(upperSide);
	line.setPosition(sf::Vector2f(x, y));
	line.setSize(sf::Vector2f(xSize, 2)); window.draw(line);
	line.setSize(sf::Vector2f(2, ySize - 1)); window.draw(line);

	line.setFillColor(lowerSide);
	line.setPosition(sf::Vector2f(x, (y + ySize) - 1));
	line.setSize(sf::Vector2f(xSize, 1)); window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize) - 1, y + 1));
	line.setSize(sf::Vector2f(1, ySize - 1)); window.draw(line);

	line.setFillColor(middleShadow);
	line.setPosition(sf::Vector2f(x + 1, (y + (ySize - 2))));
	line.setSize(sf::Vector2f(xSize - 2, 1)); window.draw(line);
	line.setPosition(sf::Vector2f((x + xSize) - 2, y + 2));
	line.setSize(sf::Vector2f(1, ySize - 3)); window.draw(line);

}

void Box::draw(sf::RenderWindow& window) {

	rectangle.setFillColor(biselB);
	if (biselPressed) { rectangle.setFillColor(pressedColor); }
	rectangle.setPosition(sf::Vector2f(x, y));
	rectangle.setSize(sf::Vector2f(xSize, ySize));
	if (isFilled) { window.draw(rectangle); }

	if (biselEnable) {
		drawBisel(window);
	}
	
	text.setFillColor(normalText);
	if (forceWhiteText) { text.setFillColor(selectedText); }

	if (highlightOnHover) {
		text.setFillColor(selectedText);
		rectangle.setFillColor(selected);
		rectangle.setPosition(sf::Vector2f(x + 3, y + 3));
		rectangle.setSize(sf::Vector2f(xSize - 7, ySize - 7));
		window.draw(rectangle);
		highlightOnHover = false;
	}

	adjustText();
	labelToDisplay = labelToDisplay + cursor;
	if (biselPressed) { text.move(1,1); }
	text.setString(labelToDisplay); window.draw(text);
	
}

