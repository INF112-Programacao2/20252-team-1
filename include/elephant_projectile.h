#include "troop_projectile.h"

class ElephantProjectile : public TroopProjectile {
private:
    static sf::Texture _texture;
    sf::RectangleShape _shape;

public:
    ElephantProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Room &room);

    void draw() override;

    static bool load_texture(std::string file_path);
};