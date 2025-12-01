#ifndef EXCAVATOR_ENEMY_H
#define EXCAVATOR_ENEMY_H

#include "enemy.h"
#include <string>

class ExcavatorEnemy : public Enemy {
private:
    static sf::Texture _texture;
    int _current_damage; // Dano atual
    int _max_damage;     // Limite maximo que o dano pode chegar
    int _ramp_up_rate;   // O quando de dano aumenta por hit

private:
    bool can_walk(double next_position) override;

    void attack(FieldTroop* field_troop) override;

public:
    ExcavatorEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room);

    void run(double dt) override;
    
    void draw() override;

    static bool load_texture(const std::string& file_path);
};

#endif