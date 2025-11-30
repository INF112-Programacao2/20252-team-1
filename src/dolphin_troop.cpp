#include "dolphin_troop.h"
#include "game_room.h"
#include "wave_manager.h"
#include "troop_manager.h"

sf::Texture DolphinTroop::_texture;

DolphinTroop::DolphinTroop(sf::Vector2f position, int line, double cooldown, Room& room)
    : Troop(position, line, cooldown, room), _attack_line(line) {
    _type = TroopType::Dolphin;
}

void DolphinTroop::run(double dt) {
    Troop::run(dt);
}

bool DolphinTroop::fire() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);
    WaveManager& wave_manager = game_room.get_wave_manager();

    std::shared_ptr<Enemy> best_target = nullptr;
    float min_x = 1000000.0f; // kkkkkkkkkkkkkkk

    // itera por todas as linhas para achar o inimigo mais perto
    for (int i = 1; i <= TROOP_ROWS; i++) {
        auto target = wave_manager.get_closest_enemy_on_line(i);
        if (target) {
            float enemy_x = target->get_position().x;
            if (enemy_x < min_x) {
                min_x = enemy_x;
                best_target = target;
            }
        }
    }

    if (best_target) {
        auto projectile = std::make_unique<DolphinProjectile>(
            _position + sf::Vector2f(50, 50),
            best_target,
            40,    // dano
            800.0, // velocidade rapido tipo um sniper
            _room);

        game_room.get_troop_manager().spawn_projectile(std::move(projectile));
        return true;
    }

    return false;
}

void DolphinTroop::draw() {
    sf::RectangleShape sprite(sf::Vector2f(100, 100));
    sprite.setPosition(_position);
    sprite.setTexture(&_texture);
    _room.get_window().draw(sprite);
}

sf::Texture& DolphinTroop::get_texture() {
    return _texture;
}

bool DolphinTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}