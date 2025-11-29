#ifndef DOLPHIN_PROJECTILE_H
#define DOLPHIN_PROJECTILE_H

#include "troop_projectile.h"

class DolphinProjectile : public TroopProjectile {
private:
    static sf::Texture _texture;
    sf::CircleShape _shape;

public:
    DolphinProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Room &room);

    void draw() override;

    static bool load_texture(std::string file_path);
};


#endif // !DOLPHIN_PROJECTILE_H
