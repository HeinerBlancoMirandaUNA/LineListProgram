#pragma once
#include "doubly_linked_list.h"
#include "point.h"
#include "math.h"
#include <SFML/Graphics.hpp>

class ListManager
{
private:

	static const int circleRadius = 10;
	sf::RectangleShape rectangle;
	sf::CircleShape circle;
	void drawPoint(sf::RenderWindow& window, Point A);
	void drawLine(sf::RenderWindow& window, Point A, Point B);	

public:
	ListManager();
	virtual ~ListManager();
	int currentRoute;
	DoublyLinkedList<DoublyLinkedList<Point>> Routes;
	void renderList(sf::RenderWindow &window);
	void addPoint(Point A);
	void delPoint(int thisPosition);
	void setPoint(int thisPosition, Point A);
	void undoPoint();
	int collidingWith(UserInteraction& User);

};

