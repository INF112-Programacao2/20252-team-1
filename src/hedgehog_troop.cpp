#include <iostream> //! DEBUG
#include "hedgehog_troop.h"
#include "game_manager.h"

sf::Texture HedgehogTroop::_texture;

HedgehogTroop::HedgehogTroop(sf::Vector2f position, float activation_radius,
                             double activation_delay, GameRoom &room)
    : FieldTroop(position, activation_radius, activation_delay, room) {}

void HedgehogTroop::run(double dt) {
    // bloqueia o resto se estiver morto
    if (_destroyed)
        return;

    // bloqueia o resto ate o cooldown acabar e se destruir
    if (_waiting_cooldown) {
        _timer.update(dt);

        double multiplier = GameManager::get_instance().get_cooldown_multiplier();
        if (_timer.get_seconds_elapsed() >= _activation_delay * multiplier) {
            GameRoom &game_room = dynamic_cast<GameRoom &>(_room);
            for (std::shared_ptr<Enemy> enemy : game_room.get_wave_manager().get_enemys_on_circle(_position, _activation_radius)) {
                enemy->damage(50); //! valor debug
            }

            destroy();
        }

        return;
    }

    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);
    if (!game_room.get_wave_manager().get_enemys_on_circle(_position, _activation_radius).empty()) {
        _waiting_cooldown = true;
    }
}

void HedgehogTroop::draw() {
    float side = 60;

    sf::RectangleShape rect(sf::Vector2f(side, side));
    rect.setPosition(_position - sf::Vector2f(side / 2, side / 2));
    rect.setTexture(&_texture);

    _room.get_window().draw(rect);

    //! DEBUG PRA VISUALIZAR O RAIO DE EXPLOSAO
    if (_waiting_cooldown) {
        sf::CircleShape circ(_activation_radius);
        circ.setPosition(_position - sf::Vector2f(_activation_radius, _activation_radius));
        _room.get_window().draw(circ);
    }
}

void HedgehogTroop::destroy() {
    std::cout << "BOOOM" << std::endl;
    _destroyed = true;
}

bool HedgehogTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}

sf::Texture &HedgehogTroop::get_texture() {
    return _texture;
}