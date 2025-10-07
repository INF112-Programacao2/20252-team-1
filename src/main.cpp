#include <SFML/Graphics.hpp>
#include <iostream>
#include "room_manager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Jogo");

    // loop principal
    while (window.isOpen()) {
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // exemplo:
        sf::CircleShape circle = sf::CircleShape(75.0);
        circle.setFillColor(sf::Color::Green);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
