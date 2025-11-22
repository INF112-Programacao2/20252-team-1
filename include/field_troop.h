#ifndef FIELD_TROOP_H
#define FIELD_TROOP_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "clock.h"
#include "globals.h"

// Classe abstrata para tropas que ficam na area dos inimigos
class FieldTroop {
protected:
    TroopType _type = TroopType::None;
    sf::Vector2f _position;
    Clock _timer;
    float _activation_radius;
    double _activation_delay;
    bool _destroyed = false;
    Room &_room;

protected:
    virtual void destroy() = 0;

public:
    FieldTroop(sf::Vector2f position, float activation_radius, double activation_delay, Room &room)
        : _position(position), _activation_radius(activation_radius),
          _activation_delay(activation_delay), _room(room) {}

    virtual ~FieldTroop() = default;

    virtual void run(double dt) = 0;

    virtual void draw() = 0;

    bool is_destroyed() { return _destroyed; }

    TroopType get_type() { return _type; }

    sf::Vector2f get_position() { return _position; }
};

#endif