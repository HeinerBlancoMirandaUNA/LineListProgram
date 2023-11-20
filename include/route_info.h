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
	int lineLight;
	sf::Uint8 red, green, blue, line;
	bool isVisible;

};

