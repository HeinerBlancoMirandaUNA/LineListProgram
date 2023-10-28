#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	User.rebuildWindow(window);
	box.button("Windows 2000 Professional");
	
}

UserInterface::~UserInterface() {

}

void UserInterface::update(sf::RenderWindow& window) {

	User.update(window);

	Box mark;
	mark.x = 30; mark.y = 30;
	mark.xSize = 360; mark.ySize = 300;

	std::cout << User.key;
	box.x = 100; box.y = 100;
	
	if (User.key > 0) {
		if (User.key == 8) { box.label.pop_back(); }
		else { box.label = box.label + User.key; }
		box.inputField(box.label);
		box.setPressedColor(70,255,70);
	}

	if (User.clickL and box.isTouching(User)) { box.press(); }
	if (!User.clickL) { box.release(); }

	mark.draw(window);
	box.draw(window);

}