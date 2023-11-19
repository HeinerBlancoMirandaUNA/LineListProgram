#include "./list_manager.h"

ListManager::ListManager() {
	List.add(First);
	position = 1;
}

ListManager::~ListManager() {

}

void ListManager::drawPoint(sf::RenderWindow& window, Point A) {

	float Ax = static_cast<float>(A.x);
	float Ay = static_cast<float>(A.y);
	
	circle.setScale(1,1);
	circle.setRadius(19);
	circle.setPosition(Ax, Ay);
	circle.move(-circle.getRadius(), -circle.getRadius());
	
	circle.setFillColor(sf::Color(45,0,45));
	window.draw(circle);
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(circle.getRadius() -1);
	window.draw(circle);

	circle.setFillColor(sf::Color::White);
	circle.setRadius(circle.getRadius() / 4);
	circle.setScale(0.75, 1.25);
	circle.move(circle.getRadius() * 1.25, circle.getRadius());
	window.draw(circle);
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
	auto temp = List.current;
	Point A, B;

	List.go(First);

	while (List.isValid()) {
		List.current->data.go(First);
		while (List.current->data.isValid() && List.current->data.getSize() > 1) {
			A = List.current->data.getItem();
			List.current->data.go(Next);
			if (!List.current->data.isValid()) { break; }
			B = List.current->data.getItem();
			List.current->data.go(Back);
			drawLine(window, A, B);
			List.current->data.go(Next);
		}

		List.current->data.go(First);
		while (List.current->data.isValid()) {
			A = List.current->data.getItem();
			drawPoint(window, A);
			List.current->data.go(Next);
		}
		List.go(Next);
	}

	List.current = temp;

}

void ListManager::addPoint(Point A) {
	List.go(position);
	if (!List.isValid()) { return; }
	List.current->data.add(Last, A);
}

void  ListManager::delPoint(int thisPosition) {
	List.go(position);
	if (!List.isValid()) { return; }
	List.current->data.del(thisPosition);
}

int ListManager::collidingWith(UserInteraction& User) {
	//auto temp = List.current;
	int toReturn = -1;

	List.go(position);
	if (!List.isValid()) { return toReturn; }
	int inPosition = 1;
	
	List.current->data.go(First);
	while (List.current->data.isValid()) {
		if (List.current->data.getItem().isTouching(User, 20)) { toReturn = inPosition; }
		List.current->data.go(Next);
		inPosition++;
	}
	
	List.go(Next);

	//List.current = temp;
	return toReturn;

}

