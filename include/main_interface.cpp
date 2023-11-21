#include "main_interface.h"

MainInterface::MainInterface(sf::RenderWindow& window) {
	resetInterface(window);
	dragPoint = false;
	lastPointPosition = 1;
	srand(time(NULL));
	Map.setScale(2, 2);
	Texture.setSmooth(true);
	Texture.loadFromFile("./resources/Map.png");
	Map.setTexture(Texture);
	FileInput.label = "NuevaLista.rdl";
}

MainInterface:: ~MainInterface() {

}

void MainInterface::routeSelector(sf::RenderWindow& window) {
	RouteItem.press();
	float spacing = 5;
	RouteItem.x = Deco.x + spacing;
	RouteItem.y = Deco.y + spacing;
	RouteItem.xSize = Deco.xSize - (spacing*2);
	RouteItem.autoAdjust = false;

	Metadata.go(First);
	while (Metadata.isValid()) {
		RouteItem.release();
		RouteItem.setPressedColor(Metadata.getItem().getColor());
		if (RouteItem.isTouching(User) && (User.clickL || User.clickR))
		{
			currentRoute = Metadata.position(); User.clickL = false;
		}
		if (Metadata.position() == currentRoute) { RouteItem.press(); }
		RouteItem.label = Metadata.getItem().name;
		if (!Metadata.getItem().isVisible) {
			RouteItem.label = RouteItem.label + "[" + char(33) + "]";
		}
		RouteItem.draw(window);
		RouteItem.y = RouteItem.y + (RouteItem.ySize + spacing);
		Metadata.go(Next);
	}
}

void MainInterface::displayForm(sf::RenderWindow& window) {

	int action = -1;
	if (Form == Hide) { 
		if (!dragPoint) { lastPointPosition = collidingWith(User); }
		lastPoint.x = static_cast<int>(User.x -xMap);
		lastPoint.y = static_cast<int>(User.y -yMap);
		lastCenterX = User.centerXdist + (Deco.xSize / 2);
		lastCenterY = User.centerYdist;
		return; 
	}

	// Context Menus

	string showOrHide = "Mostrar";
	Metadata.go(currentRoute);
	if (Metadata.getItem().isVisible) { showOrHide = "Ocultar"; };

	if (Form == MenuNothing) {
		action = Menu(window,{ "Nueva ruta"});
		if (action == 0) { newRoute(); }
		User.clickL = false;
		return;
	}

	if (Form == MenuSidebar) {
		action = Menu(window, { "Ir a cola", "Ir a cabeza", showOrHide ,"Renombrar","Cambiar color...","Nueva ruta","Borrar ruta"});
		
		if (action == 0) { moveMapToPoint(Last, lastCenterX, lastCenterY); }
		if (action == 1) { moveMapToPoint(First, lastCenterX, lastCenterY); }
		if (action == 2) { showHide(); }
		if (action == 3) {
			Metadata.go(currentRoute);
			RenameInput.label = Metadata.getItem().name;
			Form = Rename;
		}
		if (action == 4) {
			Metadata.go(currentRoute);
			lastColor = Metadata.getItem().getColor();
			Form = ColorSelector;
		}
		if (action == 5) { newRoute(); }
		if (action == 6) { delRoute(); }
		
		User.clickL = false;
		return;
	}

	if (Form == MenuCurrentRoute) {
		
		string firstOption = "Agregar punto";
		if (lastPointPosition > 0) { firstOption = "Borrar punto"; }
		action = Menu(window, { "Ir aqui", firstOption , "Borrar último" , showOrHide ,"Renombrar","Cambiar color...","Nueva ruta","Borrar ruta"});
		User.clickL = false;

		if (action == 0) {
			moveMap(xMap + lastCenterX, yMap + lastCenterY, 60);
		}
		if (action == 1) {
			if (lastPointPosition > 0) { delPoint(lastPointPosition);  }
			else { addPoint(lastPoint); }
		}
		if (action == 2) { undoPoint(); }
		if (action == 3) { 	showHide(); }
		if (action == 4) { 
			Metadata.go(currentRoute);
			RenameInput.label = Metadata.getItem().name;
			Form = Rename;
		}
		if (action == 5) {
			Metadata.go(currentRoute);
			lastColor = Metadata.getItem().getColor();
			Form = ColorSelector;
		}
		if (action == 6) { newRoute(); }
		if (action == 7) { delRoute(); }

		return;
	}

	// Windows and Dialogs

	bool isInput = Form == OpenFile || Form == SaveFile || Form == Rename;
	if (isInput) { adjustWindow(440, 110); }
	if (Form == InfoDialog) { adjustWindow(400, 130); }
	if (Form == ColorSelector) { adjustWindow(380, 180); }

	float tX = WindowForm.x + 5;
	float tY = WindowForm.y + WindowForm.ySize - 30;
	WindowForm.draw(window);

	if (Form == OpenFile) {
		Title.label = "Escriba el nombre de arhivo";
		action = Toolbar(window, tX, tY, { "Abrir","Cancelar" });
		FileInput.textField(WindowForm, 68, User);
		FileInput.draw(window);
		if (action == 0) { 
			int error = readFile(FileInput.label);

			if (error == 0) {
				loadList();
				moveMapToPoint(Last, lastCenterX, lastCenterY);
			}
			if (error == -1) {
				tellUser("Error", "No se pudo encontrar el archivo especificado");
				return;
			}
			if (error == -2) {
				tellUser("Error", "El archivo especificado no tiene un formato válido o es incompatible con esta version del programa."); 
				return;
			}
		}
	}

	if (Form == SaveFile) {
		Title.label = "Guardar como...";
		action = Toolbar(window, tX, tY, { "Guardar","Cancelar" });
		FileInput.textField(WindowForm, 68, User);
		FileInput.draw(window);
		if (action == 0) {
			saveList(FileInput.label);
			//tellUser("Error", "Hubo un problema al guardar el archivo. Intente guardar en otra ubicacion o pruebe un nombre de archivo distinto."); return; 
		}
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
		if (action == 0) {
			Metadata.go(currentRoute);
			RouteInfo toReplace = Metadata.getItem();
			toReplace.name = RenameInput.label;
			Metadata.setItem(toReplace);
		}
	}

	if (Form == ColorSelector) {
		Title.label = "Seleccione un color";
		action = Toolbar(window, tX, tY, { "Aceptar", "Al azar", "Cancelar"});
		sf::Color NewColor(colorPicker(window));

		Metadata.go(currentRoute);
		RouteInfo toReplace = Metadata.getItem();
		if (NewColor != sf::Color::Black) {
			toReplace.setColor(NewColor);
			Metadata.setItem(toReplace);
		}

		if (action == 1) { 
			sf::Color random(rand() % 255, rand() % 255, rand() % 255);
			toReplace.setColor(random);
			Metadata.setItem(toReplace);
			return;
		}
		if (action == 2) {
			toReplace.setColor(lastColor);
			Metadata.setItem(toReplace);
		}
		
	}

	if (action > -1) { Form = Hide; }
	Title.draw(window);
	User.clickL = false;

}

void MainInterface::update(sf::RenderWindow& window) {

	Map.setPosition(xMap,yMap);
	window.draw(Map);
	renderList(window);

	Metadata.go(currentRoute);	bool currentIsVisible = Metadata.getItem().isVisible;

	if (dragPoint) {
		if (User.clickL) { dragPoint = false; }
		setPoint(window, lastPointPosition, lastPoint);
		User.clickL = false;
		User.clickR = false;
	}

	bool touchingSidebars = drawSidebars(window);
	int action = Toolbar(window, 4, 4, { "Abrir","Guardar","Ayuda","Salir" });
	routeSelector(window);
	
	if (User.clickL && Form==Hide && !touchingSidebars) {
		if (currentIsVisible) {
			if (lastPointPosition > 0) { dragPoint = true; }
			else { addPoint(lastPoint); }
		}
		else {
			tellUser("No se puede editar", "La ruta actual se encuentra oculta");
		}
	}
	User.update(window);
	displayForm(window);

	if (User.clickR && Form == Hide && !dragPoint) {
		if (touchingSidebars) {
			Form = MenuSidebar;
			WindowForm.x = User.x; WindowForm.y = User.y;
		}
		else {
			Form = MenuNothing;
			if (Routes.getSize() > 0) { Form = MenuCurrentRoute; }
			WindowForm.x = User.x; WindowForm.y = User.y;
		}
		
	}
	
	holdButton(window);
	if (action == 0) { Form = OpenFile; }
	if (action == 1) { Form = SaveFile; }
	if (action == 2) { tellUser("Ayuda", "Use clic izquierdo sobre el mapa para agregar puntos a la ruta actual o click derecho para cambiar sus propiedades. Use el panel izquierdo para seleccionar o agregar otra ruta."); }
	if (action == 3) { window.close(); }

}