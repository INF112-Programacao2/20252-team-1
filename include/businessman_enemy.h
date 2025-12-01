#ifndef BUSINESSMAN_ENEMY_H
#define BUSINESSMAN_ENEMY_H

#include "enemy.h"

class BusinessmanEnemy : public Enemy {
private:
    double _heal_radius;
    int _heal_amount;

    // variaveis de controle da sequencia de ataque
    bool _is_attacking = false;
    int _shots_fired = 0;
    Clock _rapid_fire_timer;

    static sf::Texture _texture;
    static sf::Texture _projectile_texture;

private:
    bool can_walk(double next_position) override;

    void attack(FieldTroop *field_troop) override;

    void fire_projectile();

    void heal_allies();

public:
    BusinessmanEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int heal_amount, double heal_radius, int points, Room &room);

    void run(double dt) override;

    void draw() override;

    static bool load_texture(const std::string &file_path);

    static bool load_projectile_texture(const std::string &file_path);
};

#endif // !BUSINESSMAN_ENEMY_H