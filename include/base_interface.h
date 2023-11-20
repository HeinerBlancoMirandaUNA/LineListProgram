#pragma once
#include "file_load_and_save.h"
#include "box.h"
using std::string;
using std::vector;

enum UiForm {
	Hide,
	InfoDialog,
	MenuCurrentRoute,
	MenuSidebar,
	MenuNothing,
	YesNoDialog,
	OpenFile,
	SaveFile,
	Rename,
	ColorSelector
};

class BaseInterface : public Colors
{
public:
	BaseInterface();
	~BaseInterface();
	void update(sf::RenderWindow& window);

protected:

	UserInteraction User;
	Box Deco, Button, Info, LastPressed, FileInput, RenameInput, WindowForm, Title, ColorPick;;
	UiForm Form;

	int Toolbar(sf::RenderWindow& window, float x, float y, vector<string> arguments);
	int Menu(sf::RenderWindow& window, vector<string> arguments);
	sf::Color colorPicker(sf::RenderWindow& window);

	void resetInterface(sf::RenderWindow& window);
	void holdButton(sf::RenderWindow& window);
	void adjustWindow(float xSize, float ySize);
	void tellUser(string title, string body);
	
	bool drawSidebars(sf::RenderWindow& window);
	Colors::biselA;

};

