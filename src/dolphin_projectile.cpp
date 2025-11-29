#include "dolphin_projectile.h"

sf::Texture DolphinProjectile::_texture;

DolphinProjectile::DolphinProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Room& room)
    : TroopProjectile(position, target, damage, speed, room, ProjectileType::DolphinProjectileType), _shape(15.0f) {
    _shape.setTexture(&_texture);
    _shape.setOrigin(sf::Vector2f(15.0f, 15.0f)); // projetil menor
}

void DolphinProjectile::draw() {
    _shape.setPosition(_position);
    _room.get_window().draw(_shape);
}

bool DolphinProjectile::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}