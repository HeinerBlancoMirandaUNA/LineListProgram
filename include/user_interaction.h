#pragma once
#include <SFML/Graphics.hpp>

class UserInteraction
{
private:
	sf::Event event;
	void textInput();

public:
	UserInteraction();
	~UserInteraction();
	bool clickL, clickR, resize, released;
	char key;
	float x, y, width, height;
	void rebuildWindow(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	
};

