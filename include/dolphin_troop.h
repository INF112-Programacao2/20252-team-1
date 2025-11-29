#ifndef DOLPHIN_TROOP_H
#define DOLPHIN_TROOP_H

#include "troop.h"
#include  "dolphin_projectile.h"

class DolphinTroop : public Troop {
private:
    int _attack_line;
    static sf::Texture _texture;

public:
    DolphinTroop(sf::Vector2f position, int line, double cooldown, Room& room);
    
    void run(double dt) override;
    
    bool fire() override;
    
    void draw() override;
    
    static sf::Texture& get_texture();
    
    static bool load_texture(std::string file_path);
};

#endif // !DOLPHIN_TROOP_H