#pragma once
#include "doubly_linked_list.h"
#include "point.h"
#include "math.h"
#include <SFML/Graphics.hpp>

class ListManager
{
private:
	sf::RectangleShape rectangle;
	sf::CircleShape circle;
	

public:
	ListManager();
	virtual ~ListManager();
	DoublyLinkedList<DoublyLinkedList<Point>> List;
	void drawPoint(sf::RenderWindow& window, Point A);
	void drawLine(sf::RenderWindow& window, Point A, Point B);
	void renderList(sf::RenderWindow &window);

};

