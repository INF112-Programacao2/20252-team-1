#include "anteater.h"
#include "game_room.h"

sf::Texture AnteaterTroop::_texture;
sf::Texture AnteaterTroop::_projectile_texture;

AnteaterTroop::AnteaterTroop(sf::Vector2f position, int line, double cooldown, Room &room)
    : Troop(position, line, cooldown, room) {}

void AnteaterTroop::draw() {
    sf::RectangleShape rect({100, 100});
    rect.setPosition(_position);
    rect.setTexture(&_texture);

    _room.get_window().draw(rect);
}

bool AnteaterTroop::fire() {
    // atira no inimigo mais perto
    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);
    std::shared_ptr<Enemy> target = game_room.get_wave_manager().get_closest_enemy_on_line(_line);

    if (target) {
        auto projectile = std::make_unique<TroopProjectile>(
            _position + sf::Vector2f(50, 50),
            target, 30, 350.0, _room, ProjectileType::AnteaterProjectileType);

        projectile->set_texture(&_projectile_texture, 30.f);
        game_room.get_troop_manager().spawn_projectile(std::move(projectile));

        return true;
    }

    return false;
}

sf::Texture &AnteaterTroop::get_texture() {
    return _texture;
}

bool AnteaterTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}

bool AnteaterTroop::load_projectile_texture(std::string file_path) {
    return _projectile_texture.loadFromFile(file_path);
}