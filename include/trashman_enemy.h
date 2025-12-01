#ifndef TRASHMAN_ENEMY_H
#define TRASHMAN_ENEMY_H

#include "enemy.h"
#include <string>

class TrashmanEnemy : public Enemy {
private:
    static sf::Texture _texture;

private:
    bool can_walk(double next_position) override;

    void attack(FieldTroop* field_troop) override;

public:
    TrashmanEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room& room);
    
    void run(double dt) override;

    void draw() override;
    
    static bool load_texture(const std::string& file_path);
};


#endif // !TRASHMAN_ENEMY_H
