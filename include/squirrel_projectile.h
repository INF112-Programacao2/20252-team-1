#ifndef SQUIRREL_PROJECTILE_H
#define SQUIRREL_PROJECTILE_H

#include "troop_projectile.h"

class SquirrelProjectile : public TroopProjectile {
private:
    double _radius; // raio da explosao
    double _v_speed = -90;
    static sf::Texture _texture;
    sf::RectangleShape _shape;

protected:
    void on_hit(std::shared_ptr<Enemy> enemy) override; // quando atinge, explode em raio

public:
    SquirrelProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, double radius, Room& room);

    double get_radius();

    void set_radius(double radius);

    void run(double dt) override;

    void draw() override;

    static bool load_texture(std::string file_path);
};


#endif // !SQUIRREL_PROJECTILE_H
