#ifndef SOLAR_ENERGY_TROOP_H
#define SOLAR_ENERGY_TROOP_H

#include "troop.h"
#include <string>

class SolarEnergyTroop : public Troop {
private:
    int _increase_points;
    static sf::Texture _texture;

public:
    SolarEnergyTroop(sf::Vector2f position, double cooldown, int increase_points, Room &room);

    /// Gera pontos
    void fire() override;

    void draw() override;

    static sf::Texture &get_texture();

    static bool load_texture(std::string file_path);
};

#endif