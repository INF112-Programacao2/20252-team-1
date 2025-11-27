#ifndef ELEPHANT_TROOP_H
#define ELEPHANT_TROOP_H

#include "troop.h"
#include "elephant_projectile.h"

class ElephantTroop : public Troop {
private:
    static sf::Texture _texture;

public:
    ElephantTroop(sf::Vector2f position, int line, double cooldown, Room& room);
    
    void run(double dt) override;
    
    void fire() override;
    
    void draw() override;
    
    static sf::Texture& get_texture();
    
    static bool load_texture(std::string file_path);
};


#endif // !ELEPHANT_TROOP_H
