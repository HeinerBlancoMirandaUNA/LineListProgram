#include "./list_manager.h"

ListManager::ListManager() {
	newRoute();
	currentRoute = 1;
}

ListManager::~ListManager() {

}

void ListManager::drawPoint(sf::RenderWindow& window, Point A, int radius) {

	float Ax = static_cast<float>(A.x);
	float Ay = static_cast<float>(A.y);
	
	circle.setScale(1,1);
	circle.setRadius(radius);
	circle.setPosition(Ax, Ay);
	circle.move(-circle.getRadius(), -circle.getRadius());
	
	circle.setFillColor(sf::Color(45,0,45));
	window.draw(circle);
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(circle.getRadius() -1);
	window.draw(circle);

	circle.setFillColor(sf::Color(255,255,230,230));
	circle.setRadius(circle.getRadius() / 4);
	circle.setScale(0.75, 1.25);
	circle.move(circle.getRadius() * 1.25, circle.getRadius());
	window.draw(circle);
	circle.setFillColor(sf::Color::White);
}

void ListManager::drawLine(sf::RenderWindow& window, Point A, Point B) {
	
	float Ax = static_cast<float>(A.x);
	float Ay = static_cast<float>(A.y);
	float Bx = static_cast<float>(B.x);
	float By = static_cast<float>(B.y);
	
	rectangle.setPosition(Ax, Ay);

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
	rectangle.setSize(sf::Vector2f(distance,5));
	rectangle.setOrigin(0,rectangle.getSize().y/2);
	rectangle.setRotation(angle);
	window.draw(rectangle);
}

void ListManager::renderList(sf::RenderWindow& window) {
	auto temp = Routes.current;
	Point A, B;

	Routes.go(First);

	while (Routes.isValid()) {
		Routes.current->data.go(First);
		while (Routes.current->data.isValid() && Routes.current->data.getSize() > 1) {
			A = Routes.current->data.getItem();
			Routes.current->data.go(Next);
			if (!Routes.current->data.isValid()) { break; }
			B = Routes.current->data.getItem();
			Routes.current->data.go(Back);
			drawLine(window, A, B);
			Routes.current->data.go(Next);
		}

		Routes.current->data.go(First);
		while (Routes.current->data.isValid()) {
			A = Routes.current->data.getItem();
			drawPoint(window, A, circleRadius);
			Routes.current->data.go(Next);
		}
		Routes.go(Next);
		
	}

	Routes.current = temp;

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

int ListManager::collidingWith(UserInteraction& User) {
	int toReturn = -1;

	Routes.go(currentRoute);
	if (!Routes.isValid()) { return toReturn; }
	int inPosition = 1;
	
	Routes.current->data.go(First);
	while (Routes.current->data.isValid()) {
		if (Routes.current->data.getItem().isTouching(User, circleRadius)) { toReturn = inPosition; }
		Routes.current->data.go(Next);
		inPosition++;
		
	}
	
	Routes.go(Next);
	return toReturn;

}

