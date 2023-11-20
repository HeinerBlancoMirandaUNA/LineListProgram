#pragma once
#include <SFML/Graphics.hpp>

class UserInteraction
{
private:
	sf::Event event;
	void textInput();
	sf::Clock clock;

public:
	UserInteraction();
	~UserInteraction();
	bool clickL, clickR, resize, released;
	char key;
	float x, y, width, height, centerXdist, centerYdist;
	int timer;
	void rebuildWindow(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	
};

