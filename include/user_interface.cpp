#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	User.rebuildWindow(window);
}

UserInterface::~UserInterface() {

}

void UserInterface::update(sf::RenderWindow& window) {

	User.update(window);
	std::cout << User.key;
	box.x = User.x + 50; box.y = User.y;
	box.xSize = 200; box.ySize = 100;
	box.draw(window);

}