#ifndef FIELD_TROOP_H
#define FIELD_TROOP_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "clock.h"
#include "globals.h"
#include "health_manager.h"

// Classe abstrata para tropas que ficam na area dos inimigos
class FieldTroop {
protected:
    TroopType _type = TroopType::None;
    HealthManager _health_manager;
    sf::Vector2f _position;
    bool _destroyed = false;
    Room &_room;

protected:
    virtual void destroy() = 0;

public:
    FieldTroop(int life, sf::Vector2f position, Room &room)
        : _health_manager(1, []() {}), _position(position), _room(room) {
        // caso a tropa tenha vida:
        if (life > 0) {
            _health_manager.set_max_life(life);
            _health_manager.set_life(life);
            _health_manager.set_on_death_callback([this]() { this->destroy(); });
        }
    }

    virtual ~FieldTroop() = default;

    virtual void run(double dt) = 0;

    virtual void draw() = 0;

    /// Checa se a posicao esta colidindo (o default e false para as que nao tem colisao)
    virtual bool collide(sf::Vector2f position) { return false; };

    virtual void hit(int damage) { _health_manager.decrease_life(damage); }

    bool is_destroyed() { return _destroyed; }

    TroopType get_type() { return _type; }

    sf::Vector2f get_position() { return _position; }
};

#endif