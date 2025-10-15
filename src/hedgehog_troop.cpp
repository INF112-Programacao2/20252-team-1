#include <iostream> //! DEBUG
#include "hedgehog_troop.h"

HedgehogTroop::HedgehogTroop(sf::Vector2f position, float activation_radius, 
                             double activation_delay, Room &room):
    FieldTroop(position, activation_radius, activation_delay, room) {}

void HedgehogTroop::run(double dt) {
    // bloqueia o resto se estiver morto
    if (_dead)
        return;

    // bloqueia o resto ate o cooldown acabar e se destruir
    if (_waiting_cooldown) {
        if (_timer.getElapsedTime().asSeconds() >= _activation_delay) {
            // apply_area_damage();

            destroy();
        }

        return;
    }

    _timer.restart();

    // if (is_enemy_in_activation_radius()) {
    //     _waiting_cooldown = true;
    // }
}

void HedgehogTroop::draw() {
    float radius = 30;
    sf::CircleShape circle(radius);
    circle.setPosition(_position - sf::Vector2f(radius / 2, radius / 2));
    circle.setFillColor(sf::Color::Black);

    _room.get_window().draw(circle);
}

void HedgehogTroop::destroy() {
    std::cout << "BOOOM" << std::endl;
    _dead = true;
};