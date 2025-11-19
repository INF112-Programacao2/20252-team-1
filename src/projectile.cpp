#include "projectile.h"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, double speed, Room &room)
    : _position(position), _direction(direction), _speed(speed), _room(room) {

    _shape.setRadius(5.0f);
    _shape.setFillColor(sf::Color::Red);
    _shape.setOrigin(_shape.getRadius(), _shape.getRadius());
    _shape.setPosition(_position);
}

// somente debug
void Projectile::draw() {
    _shape.setPosition(_position);
    _room.get_window().draw(_shape);
}