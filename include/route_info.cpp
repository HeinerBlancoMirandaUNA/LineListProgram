#include "route_info.h"

RouteInfo::RouteInfo() {
	isVisible = true;
	name = "Nueva Ruta";
	red = 250;
	green = 60;
	blue = 28;
	line = 0;
}

RouteInfo::~RouteInfo() {

}

sf::Color RouteInfo::getColor() {
	return sf::Color(red, green, blue, 255);
}

void RouteInfo::setColor(sf::Color thisColor) {
	red = thisColor.r;
	green = thisColor.g;
	blue = thisColor.b;
}

