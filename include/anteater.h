#ifndef ANTEATER_H
#define ANTEATER_H

#include "troop.h"
#include <string>

class AnteaterTroop : public Troop {
private:
    static sf::Texture _texture;
    static sf::Texture _projectile_texture;

public:
    AnteaterTroop(sf::Vector2f position, int line, double cooldown, Room &room);

    void draw() override;

    bool fire() override;

    static sf::Texture &get_texture();

    static bool load_texture(std::string file_path);

    static bool load_projectile_texture(std::string file_path);
};

#endif