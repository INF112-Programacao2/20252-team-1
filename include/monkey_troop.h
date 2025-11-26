#ifndef MONKEY_TROOP_H
#define MONKEY_TROOP_H

#include "troop.h"
#include "monkey_projectile.h"

class MonkeyTroop : public Troop {
private:
    static sf::Texture _texture;

public:
    MonkeyTroop(sf::Vector2f position, int line, double cooldown, Room &room);

    void run(double dt) override;

    void fire() override;

    void draw() override;

    static sf::Texture &get_texture();

    static bool load_texture(std::string file_path);
};
#endif // !MONKEY_TROOP_H
