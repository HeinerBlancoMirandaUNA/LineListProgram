#include "user_interaction.h"

UserInteraction::UserInteraction(sf::RenderWindow& window) {
    clickL = false;
    clickR = false;
    resize = false;
    x = 0;
    y = 0;
    key = 0;
    rebuildWindow(window);
}

UserInteraction::~UserInteraction() {

}

void UserInteraction::rebuildWindow(sf::RenderWindow& window) {
    sf::Vector2i lastPosition = window.getPosition();
    window.create(sf::VideoMode(window.getSize().x, window.getSize().y), "Line List Program");
    window.setPosition(lastPosition);
    resize = true;
}

void UserInteraction::textInput() {

    if (event.type == sf::Event::TextEntered) {
        key = static_cast<char>(event.text.unicode);
    }

    // Backspace key = 8
    // Intro key = 13
    // Nothing = 0
}

void UserInteraction::update(sf::RenderWindow& window) {
 
    clickL = false;
    clickR = false;
    resize = false;
    key = 0;

    sf::Vector2f mousePosition;
    mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    x = mousePosition.x;
    y = mousePosition.y;
    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { window.close(); }

        if (event.type == sf::Event::MouseButtonPressed) {
            clickL = event.mouseButton.button == sf::Mouse::Left;
            clickR = event.mouseButton.button == sf::Mouse::Right;
        }
        
        if (event.type == sf::Event::Resized) { rebuildWindow(window); }
        
        textInput();
    }

}
