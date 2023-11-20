#pragma once
#include "list_manager.h"
#include "base_interface.h"

class MainInterface : public ListManager, BaseInterface
{
public:
	MainInterface(sf::RenderWindow& window);
	virtual ~MainInterface();
	void update(sf::RenderWindow& window);

private:
	int lastPointPosition;
	Point lastPoint;
	bool dragPoint;
	void displayForm(sf::RenderWindow& window);
	void routeSelector(sf::RenderWindow& window);
	//
	Box RouteItem;
};

