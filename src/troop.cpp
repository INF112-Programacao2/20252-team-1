#include "troop.h"
#include "game_manager.h"

Troop::Troop(sf::Vector2f position, Room &room)
    : _position(position), _room(room) {}

Troop::Troop(sf::Vector2f position, double cooldown, Room &room)
    : _position(position), _cooldown(cooldown), _room(room) {}

Troop::~Troop() = default;

void Troop::run(double dt) {
    _timer.update(dt);

    double cooldown = _cooldown * GameManager::get_instance().get_cooldown_multiplier();
    if (_timer.get_seconds_elapsed() >= cooldown) {
        fire();
        _timer.restart();
    }
}

void Troop::draw() {
    sf::CircleShape circle(50.0);
    circle.setPosition(_position);
    circle.setFillColor(sf::Color::Red);

    _room.get_window().draw(circle);
}