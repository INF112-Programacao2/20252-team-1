#include "troop.h"
#include "game_manager.h"
#include "game_room.h"
#include "troop_projectile.h"

Troop::Troop(sf::Vector2f position, int line, double cooldown, Room &room)
    : _position(position), _line(line), _cooldown(cooldown), _room(room) {}

Troop::~Troop() = default;

void Troop::run(double dt) {
    _timer.update(dt);

    double cooldown = _cooldown * GameManager::get_instance().get_cooldown_multiplier();
    if (_timer.get_seconds_elapsed() >= cooldown) {
        fire();
        _timer.restart();
    }
}

void Troop::fire() {
    // atira no inimigo mais perto
    GameRoom &game_room = dynamic_cast<GameRoom&>(_room);
    std::shared_ptr<Enemy> target = game_room.get_wave_manager().get_closest_enemy_on_line(_line);

    if (target) {
        game_room.get_troop_manager().spawn_projectile(std::make_unique<TroopProjectile>(
            _position + sf::Vector2f(50, 50), target, 100, 300.0, _room));
    }
}

void Troop::draw() {
    sf::CircleShape circle(50.0);
    circle.setPosition(_position);
    circle.setFillColor(sf::Color::Red);

    _room.get_window().draw(circle);
}

TroopType Troop::get_type() {
    return _type;
}