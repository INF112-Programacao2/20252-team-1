#ifndef LUMBERJACK_ENEMY_H
#define LUMBERJACK_ENEMY_H

#include "enemy.h"
#include <string>

class LumberjackEnemy : public Enemy {
private:
    static sf::Texture _texture;

private:
    void attack(FieldTroop* field_troop) override;

public:
    LumberjackEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room);

    void run(double dt) override;

    static bool load_texture(const std::string &file_path);

    double get_type_multiplier(ProjectileType type) override;
};

#endif