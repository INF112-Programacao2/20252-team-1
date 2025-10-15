#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>

// Classe abstrata para salas do jogo
class Room {
protected:
    sf::RenderWindow &_window;

public:
    Room(sf::RenderWindow &window)
        : _window(window) {}

    virtual ~Room() = default;

    // Roda toda vez que a sala e aberta, tem que dar override
    virtual void start() = 0;

    // Roda todo frame (dt e o delta time), tem que dar override
    virtual void run(double _dt, const std::vector<sf::Event> &event_queue) = 0;

    // Roda toda vez que a sala e fechada, tem que dar override
    virtual void end() = 0;

    sf::Vector2i get_mouse_position() { return sf::Mouse::getPosition(_window); };

    sf::RenderWindow &get_window() { return _window; }
};

#endif