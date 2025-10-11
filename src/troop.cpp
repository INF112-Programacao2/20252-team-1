#include <iostream> //! DEBUG
#include "troop.h"
#include "game_manager.h"

Troop::Troop(sf::Vector2f position, Room &room)
    : _position(position), _room(room) {}

Troop::Troop(sf::Vector2f position, double cooldown, Room &room)
    : _position(position), _cooldown(cooldown), _room(room) {}

Troop::~Troop() = default;

void Troop::run(double dt) {
    double cooldown = _cooldown * GameManager::get_instance().get_cooldown_multiplier();
    if (_timer.getElapsedTime().asSeconds() >= cooldown) {
        fire();
        _timer.restart();
    }
}

void Troop::fire() {
    std::cout << "fire" << std::endl;
}

void Troop::draw() {
    sf::CircleShape circle(50.0);
    circle.setPosition(_position);
    circle.setFillColor(sf::Color::Red);

    _room.get_window().draw(circle);
}

void Troop::reset_timer() {
    _timer.restart();
}