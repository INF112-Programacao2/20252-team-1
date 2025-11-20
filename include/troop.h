#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "clock.h"

// TODO: transformar numa classe abstrata
class Troop {
protected:
    sf::Vector2f _position;
    double _cooldown = 2.0;
    Clock _timer;
    Room &_room;

public:
    Troop(sf::Vector2f position, Room &room);
    Troop(sf::Vector2f position, double cooldown, Room &room);

    virtual ~Troop();

    /// Administra o cooldown da habilidade, lembra de chamar quando der override
    virtual void run(double dt);

    /// Ativa a habilidade
    virtual void fire() {}

    //! nao e virtual pura por debug
    virtual void draw();
};

#endif