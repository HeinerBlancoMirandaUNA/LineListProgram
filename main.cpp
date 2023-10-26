#include <iostream>
#include "include/user_interaction.h"

int main()
{
    std::cout << "Hello World!\n";
    sf::RenderWindow window(sf::VideoMode(640, 480), "");  
    UserInteraction User(window);

    //test stuff
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {

        User.update(window);

        std::cout << User.key;

        shape.setPosition(User.x, User.y);

        window.clear();
        window.draw(shape); // delete this
        window.display();

    }

    return 0;

}