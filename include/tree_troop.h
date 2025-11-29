#ifndef TREE_TROOP_H
#define TREE_TROOP_H

#include "field_troop.h"
#include <string>

class TreeTroop : public FieldTroop {
private:
    static sf::Texture _texture;
    sf::RectangleShape _shape;

protected:
    void destroy();

public:
    TreeTroop(int life, sf::Vector2f position, Room &room);

    void run(double dt);

    void draw();

    bool collide(sf::Vector2f position) override;

    static sf::Texture& get_texture();
    static bool load_texture(std::string file_path);
};

#endif