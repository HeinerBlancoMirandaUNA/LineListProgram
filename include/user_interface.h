#pragma once
#include "file_load_and_save.h"
#include "box.h"
using std::string;
using std::vector;

enum UiForm {
	Hide,
	InfoDialog,
	ColorSelector,
	TextInput,
	ContextMenu,
	YesNoDialog,
	FilePicker
};

class UserInterface : public FileLoadAndSave
{
public:
	UserInterface(sf::RenderWindow& window);
	~UserInterface();
	void update(sf::RenderWindow& window);

private:

	Box Deco, Button, LastPressed, Input, WindowForm, WindowLabel;
	UiForm Form;

	template<size_t total> 
	int Toolbar(sf::RenderWindow& window, float x, float y, string(&arguments)[total]);
	
	template<size_t total>
	int Menu(sf::RenderWindow& window, string(&arguments)[total]);

	void holdButton(sf::RenderWindow& window);
	void initInputField(float x, float y, float xSize);

	void show(UiForm thisForm);
	void initWindow(float xSize, float ySize);
	void formWindowUpdate(sf::RenderWindow& window);

	UserInteraction User;
	
};

