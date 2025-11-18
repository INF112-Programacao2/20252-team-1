#ifndef TROOPPROJECTILE_H
#define TROOPPROJECTILE_H

#include "projectile.h"
#include "enemy.h"
#include "room.h"
#include "troop.h"
#include "globals.h"
#include <SFML/Graphics.hpp>

class TroopProjectile : public Projectile
{
private:
    Troop &_parent;
    Enemy *_target;
    bool _valid_target = false;

public:
    TroopProjectile(sf::Vector2f position, Troop &parent, Enemy *target, double speed, Room &room);
    void run(float dt) override;
};

#endif // TROOPPROJECTILE_H