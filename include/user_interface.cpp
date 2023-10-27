#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	User.rebuildWindow(window);
}

UserInterface::~UserInterface() {

}

void UserInterface::update(sf::RenderWindow& window) {

	User.update(window);
	std::cout << User.key;
	box.x = 100; box.y = 100;
	box.xSize = User.x; box.ySize = User.y;
	if (User.key > 0) {
		if (User.key == 8) { box.label.pop_back(); }
		else { box.label = box.label + User.key; }
	}
	box.draw(window);

}