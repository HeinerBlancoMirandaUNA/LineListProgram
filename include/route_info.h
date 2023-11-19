#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using std::string;

class RouteInfo
{
public:
	RouteInfo();
	virtual ~RouteInfo();
	string name;
	sf::Color color;
	bool isVisible;

};

