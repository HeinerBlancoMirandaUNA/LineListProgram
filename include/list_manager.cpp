#include "./list_manager.h"

ListManager::ListManager() {
	newRoute();
	currentRoute = 1;
	xMap = 0;
	yMap = 0;
	gotoX = 0;
	gotoY = 0;
	timer = 0;
}

ListManager::~ListManager() {

}

void ListManager::drawPoint(sf::RenderWindow& window, Point A, int radius) {

	float Ax = static_cast<float>(A.x);
	float Ay = static_cast<float>(A.y);

	sf::Color currentColor(circle.getFillColor());
	
	circle.setScale(1,1);
	circle.setRadius(radius);
	circle.setPosition(Ax, Ay);
	circle.move(-circle.getRadius(), -circle.getRadius());
	
	circle.setFillColor(sf::Color(45,0,45,90));
	circle.move(2, 2); 
	window.draw(circle);
	circle.move(-2, -2);
	circle.setFillColor(currentColor);
	circle.setRadius(circle.getRadius() -1);
	window.draw(circle);

	circle.setFillColor(sf::Color(255,255,230,255));
	circle.setRadius(circle.getRadius() / 3.5);
	circle.setScale(0.75, 1.25);
	circle.move(circle.getRadius() * 1.25, circle.getRadius());
	window.draw(circle);

	circle.setFillColor(currentColor);
}

void ListManager::drawLine(sf::RenderWindow& window, Point A, Point B, int lineRadius) {
	
	float Ax = static_cast<float>(A.x);
	float Ay = static_cast<float>(A.y);
	float Bx = static_cast<float>(B.x);
	float By = static_cast<float>(B.y);
	
	line.setPosition(Ax, Ay);

	float distX = Ax - B.x; 
	float distY = Ay - B.y; 
	float angle = -90;
	if (distX > 0.9 || distX < -0.9 ) {
		angle = ((atan(distY / distX)) * 57.295779) + 180;
		if (distX < 0) { angle = angle - 180; }
	} else if (distY < 0) {
		angle = 90;
	}
 
	distX = distX * distX;
	distY = distY * distY;
	float distance = sqrt(distX + distY);
	line.setRotation(angle);

	line.setSize(sf::Vector2f(distance, lineRadius ));
	line.setOrigin(0, line.getSize().y/2);
	window.draw(line);

}

void ListManager::moveMap(int moveToX, int moveToY, int movTimer) {
	gotoX = moveToX;
	gotoY = moveToY;
	timer = movTimer;
}

void ListManager::updateMapPosition() {
	if (timer < 1) { return; }
	float acceleration = timer * 0.1;
	xMap = xMap + (((gotoX - xMap)) / acceleration);
	yMap = yMap + (((gotoY - yMap)) / acceleration);
	timer--;
	if (timer < 1) { xMap = gotoX;  yMap = gotoY; }
}

void ListManager::drawCurrentRoute(sf::RenderWindow& window) {
	if (!Routes.isValid()) { return; }
	
	int& lineLigth = Metadata.current->data.lineLight;
	if (!Metadata.current->data.isVisible) { lineLigth = 255; return; }

	sf::Uint8 light = lineLigth;
	sf::Color currentColor = Metadata.current->data.getColor();

	
	if (currentRoute == Routes.position()) {
		if (lineLigth < 255) { lineLigth = lineLigth + 7; }
		if (lineLigth >= 255) { lineLigth = 255; }
		
	}
	else {
		if (lineLigth > 50) { lineLigth = lineLigth - 7; }
		if (lineLigth <= 50) { lineLigth = 50; }
	}

	Point A, B;
	Routes.current->data.go(First);
	while (Routes.current->data.isValid() && Routes.current->data.getSize() > 1) {
		A = Routes.current->data.getItem();
		Routes.current->data.go(Next);
		if (!Routes.current->data.isValid()) { break; }
		B = Routes.current->data.getItem();
		Routes.current->data.go(Back);
		A.x = xMap + A.x; A.y = yMap + A.y;
		B.x = xMap + B.x; B.y = yMap + B.y;
		line.setFillColor((sf::Color(0, 0, 0, 80)));
		drawLine(window, A, B, circleRadius);
		line.setFillColor(sf::Color(currentColor.r, currentColor.g, currentColor.b,light));
		drawLine(window, A, B, circleRadius - 5);
		Routes.current->data.go(Next);
	}

	Routes.current->data.go(First);
	while (Routes.current->data.isValid()) {
		A = Routes.current->data.getItem();
		A.x = xMap+A.x; A.y = yMap + A.y;
		circle.setFillColor(currentColor);
		if (currentRoute == Routes.position()) { drawPoint(window, A, circleRadius); }
		else { drawPoint(window, A, circleRadius/2); }
		Routes.current->data.go(Next);
	}
}

void ListManager::renderList(sf::RenderWindow& window) {
	auto temp = Routes.current;

	Routes.go(First);
	Metadata.go(First);
	while (Routes.isValid()) {
		if (true) { drawCurrentRoute(window); }
		Routes.go(Next);
		Metadata.go(Next);
	}

	Routes.go(currentRoute);
	Metadata.go(currentRoute);
	drawCurrentRoute(window);
	Routes.current = nullptr;
	updateMapPosition();

}

void ListManager::addPoint(Point A) {
	Routes.go(currentRoute);
	
	if (!Routes.isValid()) { return; }
	Routes.current->data.add(Last, A);
	
}

void  ListManager::delPoint(int thisPosition) {
	Routes.go(currentRoute);
	if (!Routes.isValid()) { return; }
	Routes.current->data.del(thisPosition);
}

void ListManager::setPoint(sf::RenderWindow& window,int thisPosition, Point A) {
	Routes.go(currentRoute);
	if (!Routes.isValid()) { return; }
	Routes.current->data.go(thisPosition);
	Routes.current->data.setItem(A);
	A.x = xMap + A.x; A.y = yMap + A.y;
	drawPoint(window, A, 20);
}

void ListManager::undoPoint() {
	Routes.go(currentRoute);
	if (!Routes.isValid()) { return; }
	Routes.current->data.del(Last);
}

void ListManager::delRoute() {

	Routes.del(currentRoute);
	Metadata.del(currentRoute);
	if (currentRoute > Routes.getSize()) {
		currentRoute = Routes.getSize();
	}
	
}

void ListManager::newRoute() {
	Routes.add(Last); 
	Metadata.add(Last);
	currentRoute = Routes.getSize();
	
}

void ListManager::showHide() {
	Metadata.go(currentRoute);
	RouteInfo toChange = Metadata.getItem();
	if (toChange.isVisible) { toChange.isVisible = false; }
	else { toChange.isVisible = true; }
	Metadata.setItem(toChange);
}

int ListManager::collidingWith(UserInteraction& User) {
	int toReturn = -1;

	Routes.go(currentRoute);
	if (!Routes.isValid()) { return toReturn; }
	int inPosition = 1;
	
	Routes.current->data.go(First);
	while (Routes.current->data.isValid()) {
		Point A = Routes.current->data.getItem();
		A.x = xMap + A.x; A.y = yMap + A.y;
		if (A.isTouching(User, circleRadius+5)) { toReturn = inPosition; }
		Routes.current->data.go(Next);
		inPosition++;		
	}
	
	Routes.go(Next);
	return toReturn;

}

