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
private:
    std::weak_ptr<Enemy> _target;

protected:
    virtual void on_hit(std::shared_ptr<Enemy> enemy);

public:
    TroopProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Room &room);

    void run(double dt);
};

#endif