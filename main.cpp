#include <iostream>
#include "include/user_interface.h"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(640, 480), "Initializing...");  
    UserInterface UI(window);

    /* 
    FileLoadAndSave trash;

    trash.readFile("testDump.txt");
    for (int i = 0; i < trash.fileContents.size();i++) {
        std::cout<<trash.fileContents[i] << std::endl;
    }
    trash.saveToFile("copy.txt", trash.fileContents);
    trash.readFile("copy.txt");
    trash.saveToFile("copy2.txt", trash.fileContents);
    */

    
    while (window.isOpen()) {
        
        window.clear(sf::Color::Blue);
        UI.update(window);        
        window.display();

    }

    return 0;

}