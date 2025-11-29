#include "elephant_troop.h"
#include "game_manager.h"
#include "game_room.h"
#include "troop_manager.h"

sf::Texture ElephantTroop::_texture;

ElephantTroop::ElephantTroop(sf::Vector2f position, int line, double cooldown, Room &room)
    : Troop(position, line, cooldown, room) {
    _type = TroopType::Elephant;
}

void ElephantTroop::run(double dt) {
    Troop::run(dt);

    _sequence_timer.update(dt);

    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    double duration = _sequence_timer.get_timeout_duration();
    double time = _sequence_timer.get_seconds_elapsed();

    if (_attack_line <= 4 && time >= (_attack_line - 1) * duration / 3.0) {
        std::shared_ptr<Enemy> target = game_room.get_wave_manager().get_closest_enemy_on_line(_attack_line);
        _attack_line++;

        // so atira se tiver alvo na lane
        if (!target) {
            _sequence_timer.update(duration / 4.0); // avanca pro proximo projetil
            return;
        }

        auto projectile = std::make_unique<ElephantProjectile>(
            _position + sf::Vector2f(50, 50),
            target,
            20,    // dano
            350.0, // velocidade
            _room);

        game_room.get_troop_manager().spawn_projectile(std::move(projectile));
    }
}

void ElephantTroop::draw() {
    sf::RectangleShape sprite(sf::Vector2f(100, 100));
    sprite.setPosition(_position);
    sprite.setTexture(&_texture);
    _room.get_window().draw(sprite);
}

bool ElephantTroop::fire() {
    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    // checando se tem algum alvo
    bool has_target = false;
    for (int line = 0; line <= 4; line++) {
        if (game_room.get_wave_manager().get_closest_enemy_on_line(line)) {
            has_target = true;
            break;
        }
    }

    if (!has_target)
        return false;

    // inicia sequencia de tiros
    _sequence_timer.restart();
    _attack_line = 1;

    return true;
}

sf::Texture &ElephantTroop::get_texture() {
    return _texture;
}

bool ElephantTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}