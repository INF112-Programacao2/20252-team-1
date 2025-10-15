#ifndef HEDGEHOG_TROOP_H
#define HEDGEHOG_TROOP_H

#include "field_troop.h"

class HedgehogTroop : public FieldTroop {
protected:
    bool _waiting_cooldown = false;
protected:
    void destroy() override;

public:
    HedgehogTroop(sf::Vector2f position, float activation_radius, double activation_delay, Room &room);

    void run(double dt) override;

    void draw() override;
};

#endif