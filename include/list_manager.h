#pragma once

#include "point.h"
#include "math.h"
#include "route_info.h"
#include "file_load_and_save.h"
#include <SFML/Graphics.hpp>

class ListManager : public FileLoadAndSave
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
	void moveMapToPoint(ListPosition here, int centerX, int centerY);
	void saveList(string filename);
	void loadList();
	int collidingWith(UserInteraction& User);

};

