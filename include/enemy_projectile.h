#ifndef ENEMY_PROJECTILE_H
#define ENEMY_PROJECTILE_H

#include "projectile.h"
#include "enemy.h"
#include "wall.h"
#include "room.h"
#include "globals.h"
#include <functional>

class EnemyProjectile : public Projectile {
private:
    Enemy &_parent;
    Wall &_target;

public:
    EnemyProjectile(sf::Vector2f postition, Enemy &parent, Wall &target, double speed, Room &room);

    void run(double dt);
};

#endif
