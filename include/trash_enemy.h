#ifndef TRASH_ENEMY_H
#define TRASH_ENEMY_H

#include "enemy.h"

class TrashEnemy : public Enemy {
private:
    static sf::Texture _texture;

private:
    bool can_walk(double next_position) override;

    void attack() override;

public:
    //adicionado parametro start_x para spawnar na posicao do trashman
    TrashEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, double start_x, Room& room);

    void run(double dt) override;

    void draw() override;

    static bool load_texture(const std::string& file_path);
};

#endif