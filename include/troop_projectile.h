#ifndef TROOP_PROJECTILE_H
#define TROOP_PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "projectile.h"
#include "enemy.h"
#include "room.h"
#include "troop.h"
#include "globals.h"

class TroopProjectile : public Projectile {
protected:
    std::weak_ptr<Enemy> _target;
    bool _is_critical;

protected:
    // Chama quando o inimigo e acertado (DESTROI O PROJECTILE AQUI)
    virtual void on_hit(std::shared_ptr<Enemy> enemy);

    // Aplica o dano no inimigo e pode ainda ter um dano extra dependendo do parametro
    void apply_damage(std::shared_ptr<Enemy> enemy, double multiplier = 1.0);

public:
    TroopProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Room &room, ProjectileType type);

    void run(double dt);
};

#endif