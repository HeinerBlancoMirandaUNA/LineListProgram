#pragma once
#include "file_load_and_save.h"
#include "box.h"
using std::string;
using std::vector;

class UserInterface : public FileLoadAndSave
{
public:
	UserInterface(sf::RenderWindow& window);
	~UserInterface();
	void update(sf::RenderWindow& window);

private:

	Box Button, Deco, LastPressed, Input, Form, FormLabel;

	int popupWindow;
	void holdButton(sf::RenderWindow& window);
	void initInputField(float x, float y, float xSize);

	template<size_t total> 
	int Toolbar(sf::RenderWindow& window, float x, float y, string(&arguments)[total]);
	
	template<size_t total>
	int Menu(sf::RenderWindow& window, float x, float y, string(&arguments)[total]);

	UserInteraction User;
	

};

