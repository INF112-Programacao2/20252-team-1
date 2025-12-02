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
        if (fire()) // so reseta o timer se puder atirar
            _timer.restart();
    }
}

TroopType Troop::get_type() {
    return _type;
}