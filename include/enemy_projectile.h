#ifndef ENEMY_PROJECTILE_H
#define ENEMY_PROJECTILE_H

#include "projectile.h"
#include "enemy.h"
#include "wall.h"
#include "room.h"
#include "globals.h"
#include <functional>
#include <memory>

class EnemyProjectile : public Projectile {
private:
    std::weak_ptr<Enemy> _parent;
    Wall &_target;

public:
    EnemyProjectile(sf::Vector2f postition, std::weak_ptr<Enemy> parent, Wall &target, double speed, Room &room);

    void run(double dt);

    std::shared_ptr<Enemy> get_parent();
};

#endif
