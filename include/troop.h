#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "clock.h"
#include "globals.h"

// TODO: transformar numa classe abstrata

// TODO: passar a linha em que a troop esta

class Troop {
protected:
    TroopType _type = TroopType::Anteater;
    sf::Vector2f _position;
    int _line; // comeca do 1
    double _cooldown;
    Clock _timer;
    Room &_room;

public:
    Troop(sf::Vector2f position, int line, double cooldown, Room &room);

    virtual ~Troop();

    /// Administra o cooldown da habilidade, lembra de chamar quando der override
    virtual void run(double dt);

    /// Ativa a habilidade
    virtual bool fire() = 0;

    virtual void draw() = 0;

    TroopType get_type();
};

#endif