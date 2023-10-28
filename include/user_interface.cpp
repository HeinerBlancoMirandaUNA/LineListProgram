#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	User.rebuildWindow(window);
	popupWindow = 0;
	LastPressed.x = 0 - LastPressed.xSize;
	FormLabel.setPressedColor(0, 0, 255);
	Input.textField("Demo text field...");
	
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

template<size_t total>
int UserInterface::Menu(sf::RenderWindow& window, float x, float y, string(&arguments)[total]) {
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
	
	Deco.x = x; Deco.y = y;
	Deco.xSize = maxWidth; Deco.ySize = height+3;
	Deco.draw(window);
	Button.x = x; Button.y = y;
	for (string thisItem : arguments) {
		Button.menuItem(" " + thisItem);
		if (Button.isTouching(User) && highlightOnce) { Button.highlight(); highlightOnce = false; }
		Button.draw(window);
		Button.y = Button.y + 20;
	}
	
	return -1;

}

void UserInterface::holdButton(sf::RenderWindow& window) {
	LastPressed.draw(window);
	if (LastPressed.isPressed()) {
		window.display();
		while (!User.released) { User.update(window); }
		LastPressed.release();
		LastPressed.x = 0 - LastPressed.xSize;
	}
}

void UserInterface::initInputField(float x, float y, float xSize) {
	Input.x = x; Input.y = y; Input.xSize = xSize;
	Input.setPressedColor(70, 255, 70);

}

void UserInterface::update(sf::RenderWindow& window) {

	initInputField(200,100,200);
	if (User.key > 0) {
		if (User.key == 8) { Input.label.pop_back(); }
		else { Input.label = Input.label + User.key; }
		Input.textField(Input.label);
		Input.setPressedColor(70, 255, 70);
	}
	Input.draw(window);
	
	float toolbarHeight = 32;
	Deco.x = 0; Deco.y = 0;
	Deco.xSize = window.getSize().x; Deco.ySize = toolbarHeight; Deco.draw(window);
	Deco.y = toolbarHeight;
	Deco.xSize = 150; Deco.ySize = window.getSize().y - toolbarHeight; Deco.draw(window);

	string contents[] = {"Abrir","Guardar","Guardar como...","Salir"};
	int action = Toolbar(window, 4, 4, contents);

	User.update(window);

	if (popupWindow > 0) {
		
	}

	string context[] = { "Ocultar" , "Mostrar" , "Cambiar color..." , "Duplicar", "Borrar" , "1" , "2", "3"};
	Menu(window, 300, 300, context);

	string contentso[] = { "Aceptar", "Cancelar" };
	Toolbar(window, 30, 300, contentso);

	holdButton(window);

	if (action == 3) { window.close(); }

}