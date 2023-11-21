#include "base_interface.h"

BaseInterface::BaseInterface() {
	Form = Hide;
}

void BaseInterface::resetInterface(sf::RenderWindow& window) {
	Form = Hide;
	User.rebuildWindow(window);
	LastPressed.x = 0 - LastPressed.xSize;

	WindowForm.forceShadow();
	Title.press();
	Title.setPressedColor(accent);
	Title.forceWhite();
}


BaseInterface::~BaseInterface() {

}

int BaseInterface::Toolbar(sf::RenderWindow& window, float x, float y, vector<string> arguments) {
	bool isFirst = true;
	int toReturn = -1;
	int counter = 0;
	Button.x = x; Button.y = y;

	for (string thisItem : arguments) {
		if (!isFirst) { Button.nextTo(Button); }
		Button.button(thisItem);
		if (User.clickL and Button.isTouching(User)) { 
			LastPressed = Button; 
			LastPressed.press();
			toReturn = counter;
		}
		Button.draw(window);
		counter++;
		isFirst = false;
	}
	return toReturn;
}

int BaseInterface::Menu(sf::RenderWindow& window, vector<string> arguments) {
	int toReturn = -1;
	float maxWidth = 0;
	float height = 0;
	bool highlightOnce = true; 

	for (string thisItem : arguments) {
		Button.button(" " + thisItem);
		if (Button.labelWidth() > maxWidth) { maxWidth = Button.labelWidth(); }
		height = height + 20;
	}
	Button.xSize = maxWidth;
	
	WindowForm.xSize = maxWidth; WindowForm.ySize = height+3;
	if (WindowForm.x + WindowForm.xSize > User.width) {
		WindowForm.x = User.x - WindowForm.xSize;
	}

	if (WindowForm.y + WindowForm.ySize > User.height) {
		WindowForm.y = User.y - WindowForm.ySize;
	}
	WindowForm.draw(window);

	Button.x = WindowForm.x; Button.y = WindowForm.y;
	for (string thisItem : arguments) {
		toReturn++;
		Button.menuItem(" " + thisItem);
		if (Button.isTouching(User) && highlightOnce) { Button.highlight(); highlightOnce = false; }
		if (Button.isTouching(User) && User.clickL) { Form = Hide; return toReturn; }
		Button.draw(window);
		Button.y = Button.y + 20;
	}

	if (User.clickL) { Form = Hide; }

	return -1;

}

sf::Color BaseInterface::colorPicker(sf::RenderWindow& window) {
	ColorPick.press();
	float resetX = WindowForm.x + 10;
	ColorPick.x = resetX;
	ColorPick.y = WindowForm.y + 40;
	ColorPick.xSize = 20; ColorPick.ySize = 20;
	int red = 0; int green = 0; int blue = 0;

	sf::Color toReturn(sf::Color::Black);

	for (int y = 0; y < 5; y++) {
		red = red + 42;

		for (int x = 0; x < 18; x++) {
			blue = blue + 42;
			sf::Color option(red, green, blue % 255);
			ColorPick.setPressedColor(option);
			ColorPick.draw(window);
			if (ColorPick.isTouching(User) && User.clickL) { toReturn = option; }
			if (x % 6 == 0) { green = green + 85; }
			ColorPick.x = ColorPick.x + ColorPick.xSize;
		}
		ColorPick.x = resetX; green = 0;
		ColorPick.y = ColorPick.y + ColorPick.ySize;
	}

	return toReturn;
}

void BaseInterface::holdButton(sf::RenderWindow& window) {
	LastPressed.draw(window);
	if (LastPressed.isPressed()) {
		window.display();
		while (!User.released) { User.update(window); }
		LastPressed.release();
		LastPressed.x = 0 - LastPressed.xSize;
	}
}

void BaseInterface::adjustWindow(float xSize, float ySize) {
	int newX = (-xSize / 2) + (User.width / 2);
	int newY = (-ySize / 2) + (User.height / 2);
	WindowForm.x = static_cast<float>(newX);
	WindowForm.y = static_cast<float>(newY);
	WindowForm.xSize = xSize;
	WindowForm.ySize = ySize;
	Title.x = WindowForm.x + 5;
	Title.y = WindowForm.y + 5;
	Title.xSize = WindowForm.xSize - 10;
}

void BaseInterface::tellUser(string title, string body) {
	Title.label = title;
	Info.textLabel(body);
	Form = InfoDialog;
}

bool BaseInterface::drawSidebars(sf::RenderWindow& window) {
	bool toReturn;
	float toolbarHeight = 32;
	Deco.x = 0; Deco.y = 0;
	Deco.xSize = User.width; Deco.ySize = toolbarHeight; Deco.draw(window);
	toReturn = Deco.isTouching(User);

	Deco.y = toolbarHeight;
	Deco.xSize = 175; Deco.ySize = User.height - toolbarHeight; Deco.draw(window);
	if (!toReturn) { toReturn = Deco.isTouching(User); }
	return toReturn;
}


