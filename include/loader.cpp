#include "./loader.h"

Loader::Loader() {
	
}

Loader::~Loader() {

}

void Loader::drawPoint(sf::RenderWindow& window, Point A) {
	
	circle.setScale(1,1);
	circle.setRadius(20);
	circle.setPosition(A.x, A.y);
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

void Loader::drawLine(sf::RenderWindow& window, Point A, Point B) {
	rectangle.setPosition(A.x, A.y);
	

	float distX = A.x - B.x; 
	float distY = A.y - B.y; 
	float angle = -90;
	if (distX > 0.9 || distX < -0.9 ) {
		angle = ((atanf(distY / distX)) * 57.295779) + 180;
		if (distX < 0) { angle = angle - 180; }
	} else if (distY < 0) {
		angle = 90;
	}
	std::cout << angle << std::endl;
 
	distX = distX * distX;
	distY = distY * distY;
	float distance = sqrt(distX + distY);
	rectangle.setSize(sf::Vector2f(distance,5));
	rectangle.setOrigin(0,rectangle.getSize().y/2);
	rectangle.setRotation(angle);
	window.draw(rectangle);
}


