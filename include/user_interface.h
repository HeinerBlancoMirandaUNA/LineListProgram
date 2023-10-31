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
	Box Deco, Button, LastPressed, FileInput, RenameInput, WindowForm, WindowLabel;
	UiForm Form;

	template<size_t total> 
	int Toolbar(sf::RenderWindow& window, float x, float y, string(&arguments)[total]);
	
	template<size_t total>
	int Menu(sf::RenderWindow& window, string(&arguments)[total]);

	void holdButton(sf::RenderWindow& window);
	void adjustWindow(float xSize, float ySize);
	void updateForm(sf::RenderWindow& window);
	
};

