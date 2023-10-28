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
	Box box, Button, Deco, lastPressed;
	vector<Box> Form;
	void holdButton(sf::RenderWindow& window);
	template<size_t total> 
	int Toolbar(sf::RenderWindow& window, float x, float y, string(&arguments)[total]);
	UserInteraction User;
	

};

