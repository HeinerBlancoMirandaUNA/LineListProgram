#include <iostream>
#include "include/user_interaction.h"
#include "include/file_load_and_save.h"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(640, 480), "");  
    UserInteraction User(window);

    //test stuff
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    FileLoadAndSave trash;

    trash.readFile("testDump.txt");
    for (int i = 0; i < trash.fileContents.size();i++) {
        std::cout<<trash.fileContents[i] << std::endl;
    }
    trash.saveToFile("copy.txt", trash.fileContents);
    trash.readFile("copy.txt");
    trash.saveToFile("copy2.txt", trash.fileContents);

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