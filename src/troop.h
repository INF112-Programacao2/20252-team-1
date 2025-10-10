#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "room.h"

class Troop {
private:
    sf::Vector2f _position;
    double _cooldown = 2.0;
    sf::Clock _timer;
    Room &_room;

public:
    Troop(sf::Vector2f position, Room &room);
    Troop(sf::Vector2f position, double cooldown, Room &room);

    virtual ~Troop();

    virtual void run(double dt);

    // ativa a habilidade
    virtual void fire();

    virtual void draw();
};

#endif