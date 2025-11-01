#include <iostream> //! DEBUG
#include "hedgehog_troop.h"

sf::Texture HedgehogTroop::_texture;

HedgehogTroop::HedgehogTroop(sf::Vector2f position, float activation_radius,
                             double activation_delay, Room &room)
    : FieldTroop(position, activation_radius, activation_delay, room) {}

void HedgehogTroop::run(double dt) {
    // bloqueia o resto se estiver morto
    if (_destroyed)
        return;

    // bloqueia o resto ate o cooldown acabar e se destruir
    if (_waiting_cooldown) {
        _timer.update(dt);
        if (_timer.get_seconds_elapsed() >= _activation_delay) {
            // apply_area_damage();

            destroy();
        }

        return;
    }

    // if (is_enemy_in_activation_radius()) {
    //     _waiting_cooldown = true;
    // }
}

void HedgehogTroop::draw() {
    float side = 60;

    sf::RectangleShape rect(sf::Vector2f(side, side));
    rect.setPosition(_position - sf::Vector2f(side / 2, side / 2));
    rect.setTexture(&_texture);

    _room.get_window().draw(rect);
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