#include "point.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::~Point() {

}

bool Point::isTouching(UserInteraction& User, int radius) {
	float distX = static_cast<float>(x) - User.x;
	float distY = static_cast<float>(y) - User.y;
	distX = distX * distX;
	distY = distY * distY;
	float distance = sqrt(distX + distY);
	if (distance < radius) { return true; }
	return false;
}