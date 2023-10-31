#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	User.rebuildWindow(window);
	LastPressed.x = 0 - LastPressed.xSize;
	Form = Hide;
	Input.setPressedColor(inputBox);
	WindowLabel.press();
	WindowLabel.setPressedColor(accent);
	WindowLabel.forceWhite();
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
int UserInterface::Menu(sf::RenderWindow& window, string(&arguments)[total]) {
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
	WindowForm.draw(window);

	Button.x = WindowForm.x; Button.y = WindowForm.y;
	for (string thisItem : arguments) {
		Button.menuItem(" " + thisItem);
		if (Button.isTouching(User) && highlightOnce) { Button.highlight(); highlightOnce = false; }
		Button.draw(window);
		Button.y = Button.y + 20;
	}

	if (User.clickL) { Form = Hide; }
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

void UserInterface::show(UiForm thisForm) {
	Form = thisForm;
}

void UserInterface::initWindow(float xSize, float ySize) {
	int newX = (-xSize / 2) + (User.width / 2);
	int newY = (-ySize / 2) + (User.height / 2);
	WindowForm.x = static_cast<float>(newX);
	WindowForm.y = static_cast<float>(newY);
	WindowForm.xSize = xSize;
	WindowForm.ySize = ySize;
	WindowLabel.x = WindowForm.x + 5;
	WindowLabel.y = WindowForm.y + 5;
	WindowLabel.xSize = WindowForm.xSize - 10;
}

void UserInterface::formWindowUpdate(sf::RenderWindow& window) {
	if (Form == Hide) { return; }

	// For context menus

	if (Form == ContextMenu) {
		string contents[] = { "Ocultar" , "Mostrar" , "Cambiar color..." , "Duplicar", "Borrar" };
		Menu(window, contents);
		User.clickL = false;
		return;
	}

	// Windows and Dialogs

	int action = -1;
	WindowForm.draw(window);
	float commandsX = WindowForm.x + 5;
	float commandsY = WindowForm.y + WindowForm.ySize - 30;

	if (Form == FilePicker) {
		WindowLabel.label = "Escriba el nombre de arhivo";
		string contents[] = { "Cancelar","Abrir" };
		action = Toolbar(window, commandsX, commandsY, contents);
		Input.textField(WindowForm,40,User);
		Input.draw(window);
	}
	
	if (action == 0) { Form = Hide; }
	WindowLabel.draw(window);
	User.clickL = false;

}

void UserInterface::update(sf::RenderWindow& window) {

	float toolbarHeight = 32;
	Deco.x = 0; Deco.y = 0;
	Deco.xSize = User.width; Deco.ySize = toolbarHeight; Deco.draw(window);
	Deco.y = toolbarHeight;
	Deco.xSize = 150; Deco.ySize = User.height - toolbarHeight; Deco.draw(window);

	string contents[] = {"Abrir","Guardar","Guardar como...","Salir"};
	int action = Toolbar(window, 4, 4, contents);

	User.update(window);
	formWindowUpdate(window);

	if (User.clickR&&Form == Hide) {
		Form = ContextMenu;
		WindowForm.x = User.x; WindowForm.y = User.y;
	}

	holdButton(window);
	if (action == 0) { Form = FilePicker; initWindow(440,110);}
	if (action == 3) { window.close(); }

}