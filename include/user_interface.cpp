#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	User.rebuildWindow(window);
	box.button("Windows 2000 Professional");
	
}

UserInterface::~UserInterface() {

}

template<size_t total> int UserInterface::Toolbar(sf::RenderWindow& window, string(&arguments)[total]) {
	for (string thisItem : arguments) {
		std::cout << thisItem << std::endl;
	}
	return 0;
}

void UserInterface::update(sf::RenderWindow& window) {

	User.update(window);

	box.x = 100; box.y = 100;
	if (User.key > 0) {
		if (User.key == 8) { box.label.pop_back(); }
		else { box.label = box.label + User.key; }
		box.textField(box.label);
		box.setPressedColor(70,255,70);
	}

	if (box.isTouching(User)) { box.highlight(); }
	if (User.clickL and box.isTouching(User)) { box.press(); }
	if (User.clickR) { box.release(); }

	box.draw(window);
	/*
	float toolbarHeight = 30;
	Box Toolbar;
	Toolbar.xSize = window.getSize().x; Toolbar.ySize = toolbarHeight; Toolbar.draw(window);
	Box Sidebar; Sidebar.y = toolbarHeight;
	Sidebar.xSize = 150; Sidebar.ySize = window.getSize().y - toolbarHeight; Sidebar.draw(window);
	Box File; File.button("Abrir"); File.x = 5; File.y = 3; File.draw(window);
	Box Save; Save.button("Guardar"); Save.nextTo(File); Save.draw(window);
	Box Exit; Exit.button("Salir"); Exit.nextTo(Save); Exit.draw(window);
	

	if (User.clickL and Exit.isTouching(User)) { window.close(); }
	*/
	string contents[] = {"123","gon","meh"};
	Toolbar(window, contents);

}