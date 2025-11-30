#ifndef GUARD_TROOP_H
#define GUARD_TROOP_H

#include "troop.h"
#include "guard_projectile.h"

class GuardTroop : public Troop {
private:
    static sf::Texture _texture;

public:
    GuardTroop(sf::Vector2f position, int line, double cooldown, Room& room);
    
    void run(double dt) override;
    
    bool fire() override;
    
    void draw() override;
    
    static sf::Texture& get_texture();
    
    static bool load_texture(std::string file_path);

};

#endif // !GUARD_TROOP_H
