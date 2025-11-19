#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H

#include "projectile.h"
#include "enemy.h"
#include "wall.h"
#include "room.h"
#include "globals.h"

class EnemyProjectile : public Projectile {
private:
    Enemy &_parent;
    Wall &_target;

public:
    EnemyProjectile(sf::Vector2f postition, Enemy &parent, Wall &target, double speed, Room &room);

    void destroy() {}

    void run(double dt);
};

#endif // ENEMYPROJECTILE_H
