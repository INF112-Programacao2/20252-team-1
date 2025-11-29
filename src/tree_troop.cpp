#include "tree_troop.h"

sf::Texture TreeTroop::_texture;

TreeTroop::TreeTroop(int life, sf::Vector2f position, Room &room)
    : FieldTroop(life, position, room) {

    _type = TroopType::Tree;

    _shape.setTexture(&_texture);
    _shape.setSize({80, 80});
    _shape.setOrigin(_shape.getSize() * .5f);
    _shape.setPosition(_position);
}

void TreeTroop::destroy() {
    _destroyed = true;
}

void TreeTroop::run(double dt) {}

void TreeTroop::draw() {
    _room.get_window().draw(_shape);
    _health_manager.draw_health_bar(_room.get_window(), _position + sf::Vector2f(0, 50));
}

bool TreeTroop::collide(sf::Vector2f position) {
    return _shape.getGlobalBounds().contains(position);
}

sf::Texture &TreeTroop::get_texture() {
    return _texture;
}

bool TreeTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}