#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "globals.h"

class Projectile {
protected:
    sf::Vector2f _position;
    sf::Vector2f _direction;
    double _speed;
    int _damage;
    // Effect _effect = Effect::None;
    // double _effect_time = 0.0;
    Room &_room;
    sf::CircleShape _shape; //! shape de debug

    Projectile(sf::Vector2f position, sf::Vector2f direction, double speed, Room &room);

public:
    virtual ~Projectile() = default;

    // movimenta, atualiza direcao, checa se colidiu, da dano e aplica efeito
    virtual void run(double dt) = 0;

    // projetil eh destruido
    virtual void destroy() = 0;

    //! nao e virtual puro ainda por debug
    virtual void draw();
};

#endif
