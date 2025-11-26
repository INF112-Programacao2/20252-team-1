#include "monkey_troop.h"
#include "game_manager.h"
#include "game_room.h"
#include "troop_manager.h"

sf::Texture MonkeyTroop::_texture;

MonkeyTroop::MonkeyTroop(sf::Vector2f position, int line, double cooldown, Room& room)
    : Troop(position, line, cooldown, room), _monkey_projectile(nullptr) {
    _type = TroopType::Monkey;
}

void MonkeyTroop::run(double dt) {
    Troop::run(dt);
}

void MonkeyTroop::draw() {
    sf::RectangleShape sprite(sf::Vector2f(100, 100));
    sprite.setPosition(_position);
    sprite.setTexture(&_texture);
    _room.get_window().draw(sprite);
}

void MonkeyTroop::fire() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    std::shared_ptr<Enemy> target = game_room.get_wave_manager().get_closest_enemy_on_line(_line);

    if (target) {

        int damage = 30;           // Monkey damage
        double speed = 300.0;      // Projectile speed
        double slowdown = 0.5;     // 0.5 means 50% speed (passed to apply_slowdown)

        auto projectile = std::make_unique<MonkeyProjectile>(
            _position + sf::Vector2f(50, 50), 
            target,                           
            damage,
            speed,
            slowdown,
            _room
        );
        game_room.get_troop_manager().spawn_projectile(std::move(projectile));
    }
}


sf::Texture& MonkeyTroop::get_texture() {
    return _texture;
}


bool MonkeyTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}