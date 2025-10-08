#include <SFML/Graphics.hpp>
#include "troop_card.h"

TroopCard::TroopCard(sf::Vector2f position, float _width, TroopType troop, Room &room)
    : _position(position), _width(_width), _troop(troop), _room(room) {}

bool TroopCard::position_meeting(sf::Vector2f position) {
    float dx = position.x - _position.x;
    float dy = position.y - _position.y;

    // colisao em forma de quadrado por enquanto
    return (0 <= dx && dx <= _width && 0 <= dy && dy <= _width);
}

void TroopCard::draw() {
    sf::RectangleShape rect(sf::Vector2f(_width, _width));

    sf::Color colors[] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue,
                          sf::Color::Magenta, sf::Color::Yellow, sf::Color::White};

    rect.setFillColor(colors[_troop]);
    rect.setPosition(_position);

    _room.get_window().draw(rect);
}

TroopType TroopCard::get_troop() {
    return _troop;
}