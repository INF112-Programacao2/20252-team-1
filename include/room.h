#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>

class RoomManager;

// Classe abstrata para salas do jogo
class Room {
protected:
    sf::RenderWindow &_window;
    RoomManager &_room_manager;
    bool _paused = false;

public:
    Room(sf::RenderWindow &window, RoomManager &room_manager)
        : _window(window), _room_manager(room_manager) {}

    virtual ~Room() = default;

    // Roda toda vez que a sala e aberta, tem que dar override
    virtual void start() = 0;

    // Roda todo frame (dt e o delta time), tem que dar override
    virtual void run(double _dt, const std::vector<sf::Event> &event_queue) = 0;

    // Roda toda vez que a sala e fechada, tem que dar override
    virtual void end() = 0;

    sf::Vector2i get_mouse_position() { return sf::Mouse::getPosition(_window); };

    sf::RenderWindow &get_window() { return _window; }

    bool is_paused() { return _paused; }
};

#endif