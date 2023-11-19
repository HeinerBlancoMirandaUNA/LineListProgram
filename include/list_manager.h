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
	void drawPoint(sf::RenderWindow& window, Point A);
	void drawLine(sf::RenderWindow& window, Point A, Point B);	

public:
	ListManager();
	virtual ~ListManager();
	int position;
	DoublyLinkedList<DoublyLinkedList<Point>> List;
	void renderList(sf::RenderWindow &window);
	void addPoint(Point A);
	void delPoint(int position);
	int collidingWith(UserInteraction& User);

};

