#include <SFML/Graphics.hpp>
#include "troop_card.h"
#include "game_manager.h"

TroopCard::TroopCard(sf::Vector2f position, float _width, TroopType troop, int price, Room &room)
    : _position(position), _width(_width), _troop(troop), _price(price), _room(room) {}

bool TroopCard::position_meeting(sf::Vector2f position) {
    float dx = position.x - _position.x;
    float dy = position.y - _position.y;

    // colisao em forma de quadrado por enquanto
    return (0 <= dx && dx <= _width && 0 <= dy && dy <= _width);
}

void TroopCard::draw() {
    sf::RectangleShape rect(sf::Vector2f(_width, _width));

    sf::Color colors[TROOP_COUNT] = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta,
        sf::Color::Yellow, sf::Color::White, sf::Color::Cyan};

    rect.setFillColor(colors[_troop]);
    rect.setPosition(_position);

    _room.get_window().draw(rect);
}

TroopType TroopCard::get_troop() {
    return _troop;
}

TroopType TroopCard::buy() {
    if (GameManager::get_instance().remove_points(_price)) {
        return _troop;
    }

    return TroopType::None;
}