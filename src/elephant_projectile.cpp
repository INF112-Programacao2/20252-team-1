#include "elephant_projectile.h"
#include "game_room.h"
#include "globals.h"
#include <cmath>

sf::Texture ElephantProjectile::_texture;

const double PI = 3.141592653;

// normalize de troop_projectile.cpp posto aqui pra evitar include circular
sf::Vector2f normalize_dir(sf::Vector2f vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length == 0.0f)
        return sf::Vector2f(1.0f, 0.0f);
    return vec / length;
}

ElephantProjectile::ElephantProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Room &room)
    : TroopProjectile(position, target, damage, speed, room, ProjectileType::ElephantProjectileType) {

    _shape.setSize(sf::Vector2f(30.0f, 30.0f)); // ajuste
    _shape.setOrigin(_shape.getSize() / 2.0f);
    _shape.setTexture(&_texture);

    if (_target.expired()) {
        // default pra dreita se o alvo morreu instantaneamente
        _direction = sf::Vector2f(1.0f, 0.0f);
    }
}

void ElephantProjectile::draw() {
    _shape.setPosition(_position);
    _shape.setRotation(atan2(_direction.y, _direction.x) * 180.0 / PI);
    _room.get_window().draw(_shape);
}

bool ElephantProjectile::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}