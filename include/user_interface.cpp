#include "user_interface.h"

UserInterface::UserInterface(sf::RenderWindow& window) {

	Form = Hide;
	User.rebuildWindow(window);
	LastPressed.x = 0 - LastPressed.xSize;
	
	WindowForm.forceShadow();
	Title.press();
	Title.setPressedColor(accent);
	Title.forceWhite();
}

UserInterface::~UserInterface() {

}


int UserInterface::Toolbar(sf::RenderWindow& window, float x, float y, vector<string> arguments) {
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

int UserInterface::Menu(sf::RenderWindow& window, vector<string> arguments) {
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
	Title.x = WindowForm.x + 5;
	Title.y = WindowForm.y + 5;
	Title.xSize = WindowForm.xSize - 10;
}

void UserInterface::tellUser(string title, string body) {
	Title.label = title;
	Info.textLabel(body);
	Form = InfoDialog;
}

void UserInterface::displayForm(sf::RenderWindow& window) {
	
	int action = -1;
	if (Form == Hide) { return; }

	// Context Menus

	if (Form == ContextMenu) {
		action = Menu(window, {"Ocultar/Mostrar","Cambiar color...","Renombrar","Duplicar","Borrar"});
		User.clickL = false;

		if (action == 1) { Form = ColorSelector; }
		if (action == 2) { Form = Rename; }

		return;
	}

	// Windows and Dialogs

	bool isInput = Form==OpenFile || Form==SaveFile || Form==Rename;
	if (isInput) { adjustWindow(440, 110); }
	if (Form == InfoDialog) { adjustWindow(400, 130); }
	if (Form == ColorSelector) { adjustWindow(400, 200); }
	
	float tX = WindowForm.x + 5;
	float tY = WindowForm.y + WindowForm.ySize - 30;
	WindowForm.draw(window);

	if (Form == OpenFile) {
		Title.label = "Escriba el nombre de arhivo";
		action = Toolbar(window, tX, tY, {"Abrir","Cancelar"});
		FileInput.textField(WindowForm,68,User);
		FileInput.draw(window);
		if (action == 0) { tellUser("Error", "El archivo especificado no tiene un formato válido."); return; }
	}

	if (Form == SaveFile) {
		Title.label = "Guardar como...";
		action = Toolbar(window, tX, tY, { "Guardar","Cancelar" });
		FileInput.textField(WindowForm, 68, User);
		FileInput.draw(window);
		if (action == 0) { tellUser("Error", "Hubo un problema al guardar el archivo. Intente guardar en otra ubicacion o pruebe un nombre de archivo distinto."); return; }
	}

	if (Form == InfoDialog) {
		Info.x = WindowForm.x + 5; Info.y = WindowForm.y + 30;
		Info.xSize = WindowForm.xSize - 10; Info.ySize = WindowForm.ySize - 60;
		Info.draw(window);
		action = Toolbar(window, tX, tY, { "Aceptar" });
	}

	if (Form == Rename) {
		Title.label = "Cambiar nombre de ruta";
		action = Toolbar(window, tX, tY, { "Renombrar","Cancelar" });
		RenameInput.textField(WindowForm, 68, User);
		RenameInput.draw(window);
	}

	if (Form == ColorSelector) {
		Title.label = "Seleccione un nuevo color";
		action = Toolbar(window, tX, tY, { "Cambiar color" , "Cancelar" });
	}

	if (action > -1) { Form = Hide; }
	Title.draw(window);
	User.clickL = false;

}

void UserInterface::update(sf::RenderWindow& window) {

	float toolbarHeight = 32;
	Deco.x = 0; Deco.y = 0;
	Deco.xSize = User.width; Deco.ySize = toolbarHeight; Deco.draw(window);
	Deco.y = toolbarHeight;
	Deco.xSize = 150; Deco.ySize = User.height - toolbarHeight; Deco.draw(window);

	int action = Toolbar(window, 4, 4, { "Abrir","Guardar","Ayuda","Salir" });

	User.update(window);
	displayForm(window);

	if (User.clickR&&Form == Hide) {
		Form = ContextMenu;
		WindowForm.x = User.x; WindowForm.y = User.y;
	}

	holdButton(window);
	if (action == 0) { Form = OpenFile; }
	if (action == 1) { Form = SaveFile; }
	if (action == 2) { tellUser("Ayuda","Use clic izquierdo sobre el mapa para agregar puntos a la ruta actual o click derecho para cambiar sus propiedades. Use el panel izquierdo para seleccionar o agregar otra ruta."); }
	if (action == 3) { window.close(); }

}