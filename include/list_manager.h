#pragma once
#include "doubly_linked_list.h"
#include "point.h"
#include "math.h"
#include "route_info.h"
#include <SFML/Graphics.hpp>

class ListManager
{
private:

	static const int circleRadius = 10;
	sf::RectangleShape line;
	sf::CircleShape circle;
	int gotoX, gotoY, timer;
	
	void updateMapPosition();
	void drawPoint(sf::RenderWindow& window, Point A, int radius);
	void drawLine(sf::RenderWindow& window, Point A, Point B, int lineRadius);
	void drawCurrentRoute(sf::RenderWindow& window);

public:
	ListManager();
	virtual ~ListManager();
	int currentRoute;
	float xMap, yMap;
	DoublyLinkedList<DoublyLinkedList<Point>> Routes;
	DoublyLinkedList<RouteInfo> Metadata;
	void renderList(sf::RenderWindow &window);
	void addPoint(Point A);
	void delPoint(int thisPosition);
	void setPoint(sf::RenderWindow& window, int thisPosition, Point A);
	void delRoute();
	void newRoute();
	void showHide();
	void undoPoint();
	void moveMap(int moveToX, int moveToY, int movTimer);
	int collidingWith(UserInteraction& User);

};

