#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	Form = Hide;
	User.rebuildWindow(window);
	LastPressed.x = 0 - LastPressed.xSize;
	
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

void UserInterface::holdButton(sf::RenderWindow& window) {
	LastPressed.draw(window);
	if (LastPressed.isPressed()) {
		window.display();
		while (!User.released) { User.update(window); }
		LastPressed.release();
		LastPressed.x = 0 - LastPressed.xSize;
	}
}

void UserInterface::adjustWindow(float xSize, float ySize) {
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

void UserInterface::updateForm(sf::RenderWindow& window) {
	
	int action = -1;
	if (Form == Hide) { return; }

	// Context Menus

	if (Form == ContextMenu) {
		string contents[] = {"Ocultar/Mostrar","Cambiar color...","Renombrar","Duplicar","Borrar"};
		action = Menu(window, contents);
		User.clickL = false;

		if (action == 1) { Form = ColorSelector; }
		if (action == 2) { Form = Rename; }

		return;
	}

	// Windows and Dialogs

	bool isInputDialog = Form==OpenFile || Form==SaveFile || Form==Rename;
	if (isInputDialog) { adjustWindow(440, 110); }
	if (Form == ColorSelector) { adjustWindow(400, 200); }
	
	float commandsX = WindowForm.x + 5;
	float commandsY = WindowForm.y + WindowForm.ySize - 30;
	WindowForm.draw(window);

	if (Form == OpenFile) {
		WindowLabel.label = "Escriba el nombre de arhivo";
		string contents[] = {"Abrir","Cancelar"};
		action = Toolbar(window, commandsX, commandsY, contents);
		FileInput.textField(WindowForm,40,User);
		FileInput.draw(window);
	}

	if (Form == SaveFile) {
		WindowLabel.label = "Guardar como...";
		string contents[] = { "Guardar","Cancelar" };
		action = Toolbar(window, commandsX, commandsY, contents);
		FileInput.textField(WindowForm, 40, User);
		FileInput.draw(window);
	}

	if (Form == Rename) {
		WindowLabel.label = "Cambiar nombre de ruta";
		string contents[] = { "Renombrar","Cancelar" };
		action = Toolbar(window, commandsX, commandsY, contents);
		RenameInput.textField(WindowForm, 40, User);
		RenameInput.draw(window);
	}

	if (Form == ColorSelector) {
		WindowLabel.label = "Seleccione un nuevo color";
		string contents[] = { "Cambiar color" , "Cancelar" };
		action = Toolbar(window, commandsX, commandsY, contents);
	}

	if (action > -1) { Form = Hide; }
	WindowLabel.draw(window);
	User.clickL = false;

}

void UserInterface::update(sf::RenderWindow& window) {

	float toolbarHeight = 32;
	Deco.x = 0; Deco.y = 0;
	Deco.xSize = User.width; Deco.ySize = toolbarHeight; Deco.draw(window);
	Deco.y = toolbarHeight;
	Deco.xSize = 150; Deco.ySize = User.height - toolbarHeight; Deco.draw(window);

	string contents[] = {"Abrir","Guardar","Ayuda","Salir"};
	int action = Toolbar(window, 4, 4, contents);

	User.update(window);
	updateForm(window);

	if (User.clickR&&Form == Hide) {
		Form = ContextMenu;
		WindowForm.x = User.x; WindowForm.y = User.y;
	}

	holdButton(window);
	if (action == 0) { Form = OpenFile; }
	if (action == 1) { Form = SaveFile; }
	if (action == 3) { window.close(); }

}