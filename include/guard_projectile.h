#ifndef GUARD_PROJECTILE_H
#define GUARD_PROJECTILE_H

#include "troop_projectile.h"

class GuardProjectile : public TroopProjectile {
private:
    Clock _stun_duation;
    static sf::Texture _texture;
    sf::RectangleShape _shape;

protected:
    void on_hit(std::shared_ptr<Enemy> enemy) override; //aplica stun

public:
    GuardProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Clock stun_duration, Room& room);
    
    void run(double dt) override;
    
    void draw() override;

    Clock get_stun_duration();
    
    void set_stun_duration(Clock stun_duration);

    static bool load_texture(std::string file_path);
};
#endif // !GUARD_PROJECTILE_H