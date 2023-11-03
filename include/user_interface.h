#pragma once
#include "file_load_and_save.h"
#include "box.h"
using std::string;
using std::vector;

enum UiForm {
	Hide,
	InfoDialog,
	ContextMenu,
	YesNoDialog,
	OpenFile,
	SaveFile,
	Rename,
	ColorSelector
};

class UserInterface : public FileLoadAndSave, public Colors
{
public:
	UserInterface(sf::RenderWindow& window);
	~UserInterface();
	void update(sf::RenderWindow& window);

private:

	UserInteraction User;
	Box Deco, Button, Info, LastPressed, FileInput, RenameInput, WindowForm, Title;
	UiForm Form;

	int Toolbar(sf::RenderWindow& window, float x, float y, vector<string> arguments);
	int Menu(sf::RenderWindow& window, vector<string> arguments);
	
	void holdButton(sf::RenderWindow& window);
	void adjustWindow(float xSize, float ySize);
	void tellUser(string title, string body);
	void displayForm(sf::RenderWindow& window);
	
};

