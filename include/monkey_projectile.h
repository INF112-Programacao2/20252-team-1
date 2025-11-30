#ifndef MONKEY_PROJECTILE_H
#define MONKEY_PROJECTILE_H

#include "troop_projectile.h"

class MonkeyProjectile : public TroopProjectile {
private:
    double _slowdown_pct; // fator de slowdown no alvo
    double _v_speed = -90;
    static sf::Texture _texture;
    sf::RectangleShape _shape;

protected:
    void on_hit(std::shared_ptr<Enemy> enemy) override; // aplica slowdown

public:
    MonkeyProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, double slowdown_pct, Room &room);

    double get_slowdown_pct();

    void run(double dt) override;

    void draw() override;

    static bool load_texture(std::string file_path);
};

#endif // !MONKEY_PROJECTILE_H