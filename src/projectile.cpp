#include "projectile.h"
#include "globals.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, int damage,
                       double speed, Room &room, ProjectileType type)
    : _position(position), _direction(direction), _damage(damage), _speed(speed),
      _room(room), _type(type) {

    _shape.setRadius(30.0);
    _shape.setFillColor(sf::Color::Red);
    _shape.setOrigin(_shape.getRadius(), _shape.getRadius());
    _shape.setPosition(_position);

    if (_direction.x != 0 || _direction.y != 0) {
        float angle = std::atan2(_direction.y, _direction.x) * 180 / 3.14159;
        _shape.setRotation(angle);
    }
}

void Projectile::destroy() {
    _destroyed = true;
}

// somente debug
void Projectile::draw() {
    _shape.setPosition(_position);
    _room.get_window().draw(_shape);
}

bool Projectile::is_destroyed() {
    return _destroyed;
}

int Projectile::get_damage() {
    return _damage;
}

ProjectileType Projectile::get_type() {
    return _type;
}

void Projectile::set_texture(sf::Texture *texture, float radius) {
    _shape.setTexture(texture);
    _shape.setRadius(radius);
    _shape.setOrigin(sf::Vector2f(1, 1) * radius * .5f);
    _shape.setFillColor(sf::Color::White);
}