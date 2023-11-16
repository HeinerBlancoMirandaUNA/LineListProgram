#include "main_interface.h"

MainInterface::MainInterface(sf::RenderWindow& window) {
	resetInterface(window);
}

MainInterface:: ~MainInterface() {

}

void MainInterface::displayForm(sf::RenderWindow& window) {

	int action = -1;
	if (Form == Hide) { return; }

	// Context Menus

	if (Form == ContextMenu) {
		action = Menu(window, { "Ocultar/Mostrar","Cambiar color...","Renombrar","Duplicar","Borrar" });
		User.clickL = false;

		if (action == 1) { Form = ColorSelector; }
		if (action == 2) { Form = Rename; }

		return;
	}

	// Windows and Dialogs

	bool isInput = Form == OpenFile || Form == SaveFile || Form == Rename;
	if (isInput) { adjustWindow(440, 110); }
	if (Form == InfoDialog) { adjustWindow(400, 130); }
	if (Form == ColorSelector) { adjustWindow(400, 200); }

	float tX = WindowForm.x + 5;
	float tY = WindowForm.y + WindowForm.ySize - 30;
	WindowForm.draw(window);

	if (Form == OpenFile) {
		Title.label = "Escriba el nombre de arhivo";
		action = Toolbar(window, tX, tY, { "Abrir","Cancelar" });
		FileInput.textField(WindowForm, 68, User);
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

void MainInterface::update(sf::RenderWindow& window) {

	drawSidebars(window);
	int action = Toolbar(window, 4, 4, { "Abrir","Guardar","Ayuda","Salir" });

	User.update(window);
	displayForm(window);

	if (User.clickR && Form == Hide) {
		Form = ContextMenu;
		WindowForm.x = User.x; WindowForm.y = User.y;
	}

	holdButton(window);
	if (action == 0) { Form = OpenFile; }
	if (action == 1) { Form = SaveFile; }
	if (action == 2) { tellUser("Ayuda", "Use clic izquierdo sobre el mapa para agregar puntos a la ruta actual o click derecho para cambiar sus propiedades. Use el panel izquierdo para seleccionar o agregar otra ruta."); }
	if (action == 3) { window.close(); }

}