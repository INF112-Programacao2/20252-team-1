#ifndef HEDGEHOG_TROOP_H
#define HEDGEHOG_TROOP_H

#include "field_troop.h"
#include "game_room.h"

class HedgehogTroop : public FieldTroop {
private:
    static sf::Texture _texture;
    Clock _timer;
    float _activation_radius;
    double _activation_delay;
    int _damage;
    bool _waiting_cooldown = false;

private:
    void destroy();

public:
    HedgehogTroop(sf::Vector2f position, int damage, float activation_radius, double activation_delay, GameRoom &room);

    void run(double dt);

    void draw();

    static bool load_texture(std::string file_path);

    static sf::Texture &get_texture();
};

#endif