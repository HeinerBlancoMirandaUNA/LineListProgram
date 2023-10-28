#pragma once
#include "file_load_and_save.h"
#include "box.h"

class UserInterface : public FileLoadAndSave
{
public:
	UserInterface(sf::RenderWindow& window);
	~UserInterface();
	void update(sf::RenderWindow& window);

private:
	Box box;
	UserInteraction User;

};

