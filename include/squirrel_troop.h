#ifndef SQUIRREL_TROOP_H
#define SQUIRREL_TROOP_H

#include "troop.h"
#include "squirrel_projectile.h"

class SquirrelTroop : public Troop {
private:
    static sf::Texture _texture;

public:
    SquirrelTroop(sf::Vector2f position, int line, double cooldown, Room& room);

    void run(double dt) override;

    bool fire() override;

    void draw() override;

    static sf::Texture& get_texture();

    static bool load_texture(std::string file_path);

};


#endif // !SQUIRREL_TROOP_H
