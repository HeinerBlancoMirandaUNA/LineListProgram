#include <iostream>
#include "include/main_interface.h"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(640, 480), "Initializing...");  
    MainInterface UI(window);
      
    while (window.isOpen()) {
        
        window.clear(sf::Color::Blue);
        UI.update(window);        
        window.display();

    }

    return 0;

}