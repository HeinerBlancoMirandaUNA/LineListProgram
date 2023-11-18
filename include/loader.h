#pragma once
#include "doubly_linked_list.h"
#include "point.h"
#include "math.h"
#include <SFML/Graphics.hpp>

class Loader
{
private:
	sf::RectangleShape rectangle;
	sf::CircleShape circle;
	

public:
	Loader();
	virtual ~Loader();
	DoublyLinkedList<Point> List;
	void drawPoint(sf::RenderWindow& window, Point A);
	void drawLine(sf::RenderWindow& window, Point A, Point B);
	void renderList(sf::RenderWindow &window);

};

