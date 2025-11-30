#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "globals.h"

class Projectile {
protected:
    ProjectileType _type = ProjectileType::EnemyBaseProjectile;
    sf::Vector2f _position;
    sf::Vector2f _direction;
    double _speed;
    int _damage;
    bool _destroyed = false;
    Room &_room;
    sf::CircleShape _shape;

    Projectile(sf::Vector2f position, sf::Vector2f direction, int damage, double speed, Room &room, ProjectileType type);

public:
    virtual ~Projectile() = default;

    // projetil eh destruido
    virtual void destroy();

    // movimenta, atualiza direcao, checa se colidiu, da dano e aplica efeito
    virtual void run(double dt) = 0;

    //! nao e virtual puro ainda por debug
    virtual void draw();

    bool is_destroyed();

    int get_damage();

    ProjectileType get_type();

    /// modifica a textura e o tamanho dela
    void set_texture(sf::Texture *texture, float radius);
};

#endif
