#include "projectile.h"
#include "globals.h"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, double speed, Room &room)
    : _position(position), _direction(direction), _speed(speed), _room(room) {

    _shape.setRadius(5.0f);
    _shape.setFillColor(sf::Color::Red);
    _shape.setOrigin(_shape.getRadius(), _shape.getRadius());
    _shape.setPosition(_position);
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