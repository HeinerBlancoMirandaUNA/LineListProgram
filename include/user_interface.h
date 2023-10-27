#pragma once
#include "user_interaction.h"
#include "file_load_and_save.h"
#include "box.h"

class UserInterface : public FileLoadAndSave
{
public:
	UserInterface(sf::RenderWindow& window);
	~UserInterface();
	UserInteraction User;
	Box box;
	void update(sf::RenderWindow& window);

private:


};

