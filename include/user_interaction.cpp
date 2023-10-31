#include "user_interaction.h"

UserInteraction::UserInteraction() {
    clickL = false;
    clickR = false;
    resize = false;
    released = false;
    x = 0;
    y = 0;
    key = 0;
    width = 100;
    height = 100;
}

UserInteraction::~UserInteraction() {

}

void UserInteraction::rebuildWindow(sf::RenderWindow& window) {
    sf::Vector2i lastPosition = window.getPosition();
    window.create(sf::VideoMode(window.getSize().x, window.getSize().y), "Line List Program");
    window.setPosition(lastPosition);
    window.setFramerateLimit(60);
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
    released = false;
    key = 0;
    width = static_cast<float>(window.getSize().x);
    height = static_cast<float>(window.getSize().y);
    timer = clock.getElapsedTime().asMilliseconds();
    
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
        
        released = event.type == sf::Event::MouseButtonReleased;

        if (event.type == sf::Event::Resized) { rebuildWindow(window); }
        
        textInput();
    }

}
