#ifndef HEDGEHOG_TROOP_H
#define HEDGEHOG_TROOP_H

#include "field_troop.h"

class HedgehogTroop : public FieldTroop {
private:
    static sf::Texture _texture;
    bool _waiting_cooldown = false;

private:
    void destroy();

public:
    HedgehogTroop(sf::Vector2f position, float activation_radius, double activation_delay, Room &room);

    void run(double dt);

    void draw();

    static bool load_texture(std::string file_path);

    static sf::Texture &get_texture();
};

#endif