#ifndef SOLAR_ENERGY_TROOP_H
#define SOLAR_ENERGY_TROOP_H

#include "troop.h"

class SolarEnergyTroop : public Troop {
private:
    int _increase_points;

public:
    SolarEnergyTroop(sf::Vector2f position, double cooldown, int increase_points, Room &room);

    void fire() override;

    void draw() override;
};

#endif