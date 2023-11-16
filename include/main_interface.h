#pragma once
#include "loader.h"
#include "base_interface.h"

class MainInterface : public Loader, BaseInterface
{
public:
	MainInterface(sf::RenderWindow& window);
	virtual ~MainInterface();
	void update(sf::RenderWindow& window);

private: 
	void displayForm(sf::RenderWindow& window);
};

