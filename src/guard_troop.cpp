#include "guard_troop.h"
#include "game_room.h"
#include "game_manager.h"
#include "wave_manager.h"
#include "troop_manager.h"

sf::Texture GuardTroop::_texture;

GuardTroop::GuardTroop(sf::Vector2f position, int line, double cooldown, Room &room)
    : Troop(position, line, cooldown, room) {
    _type = TroopType::Guard;
}

void GuardTroop::run(double dt) {
    Troop::run(dt);
}

bool GuardTroop::fire() {
    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    std::shared_ptr<Enemy> target = game_room.get_wave_manager().get_closest_enemy_on_line(_line);

    if (target) {
        int damage = 55;
        double speed = 400.0;
        double stun_time = 1.5;

        // centraliza projetil
        auto projectile = std::make_unique<GuardProjectile>(
            _position + sf::Vector2f(50, 50),
            target,
            damage,
            speed,
            Clock(stun_time),
            _room);

        game_room.get_troop_manager().spawn_projectile(std::move(projectile));
        return true;
    }

    return false;
}

void GuardTroop::draw() {
    sf::RectangleShape shape({100, 100});
    shape.setTexture(&_texture);
    shape.setPosition(_position);
    _room.get_window().draw(shape);
}

sf::Texture &GuardTroop::get_texture() {
    return _texture;
}

bool GuardTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}