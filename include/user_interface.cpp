#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	User.rebuildWindow(window);
	lastPressed.x = 0 - lastPressed.xSize;
	box.button("Windows 2000 Professional");
	
}

UserInterface::~UserInterface() {

}

template<size_t total> 
int UserInterface::Toolbar(sf::RenderWindow& window, float x, float y, string(&arguments)[total]) {
	bool isFirst = true;
	int toReturn = -1;
	int counter = 0;
	Button.x = x; Button.y = y;

	for (string thisItem : arguments) {
		if (!isFirst) { Button.nextTo(Button); }
		Button.button(thisItem);
		if (User.clickL and Button.isTouching(User)) { 
			lastPressed = Button; 
			lastPressed.press();
			toReturn = counter;
		}
		Button.draw(window);
		counter++;
		isFirst = false;
	}
	return toReturn;
}

void UserInterface::holdButton(sf::RenderWindow& window) {
	lastPressed.draw(window);
	if (lastPressed.isPressed()) {
		window.display();
		while (!User.released) { User.update(window); }
		lastPressed.release();
		lastPressed.x = 0 - lastPressed.xSize;
	}
}

void UserInterface::update(sf::RenderWindow& window) {

	User.update(window);

	box.x = 100; box.y = 100;
	if (User.key > 0) {
		if (User.key == 8) { box.label.pop_back(); }
		else { box.label = box.label + User.key; }
		box.textField(box.label);
		box.setPressedColor(70, 255, 70);
	}

	if (box.isTouching(User)) { box.highlight(); }
	if (User.clickL and box.isTouching(User)) { box.press(); }
	if (User.clickR) { box.release(); }

	box.draw(window);
	
	float toolbarHeight = 32;
	Deco.y = 0;
	Deco.xSize = window.getSize().x; Deco.ySize = toolbarHeight; Deco.draw(window);
	Deco.y = toolbarHeight;
	Deco.xSize = 150; Deco.ySize = window.getSize().y - toolbarHeight; Deco.draw(window);

	string contents[] = {"Abrir","Guardar","Guardar como...","Salir"};
	int action = Toolbar(window, 4, 4, contents);

	string contentso[] = { "Abortar", "Reintentar", "Omitir" };
	Toolbar(window, 30, 300, contentso);

	holdButton(window);

	if (action == 3) {
		window.close();
	}

}