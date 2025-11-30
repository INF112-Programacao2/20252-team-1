#ifndef FIRE_ENEMY_H
#define FIRE_ENEMY_H

#include "enemy.h"
#include <string>

class FireEnemy : public Enemy {
private:
    static sf::Texture _texture;
    double _burn_duration;

private:
    bool can_walk(double next_position) override;

    void attack() override;

public:
    FireEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, double burn_duration, Room &room);

    void run(double dt) override;

    void draw() override;

    double get_type_multiplier(ProjectileType type) override;

    static bool load_texture(const std::string &file_path);
};

#endif // !FIRE_ENEMY_H
