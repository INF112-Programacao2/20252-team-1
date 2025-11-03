#include <SFML/Graphics.hpp>
#include <sstream>
#include "troop_card.h"
#include "game_manager.h"

TroopCard::TroopCard(sf::Vector2f position, float _width, TroopType troop, int price,
                     sf::Texture *texture, Room &room)
    : _position(position), _width(_width), _troop(troop), _price(price),
      _texture(texture), _room(room) {}

bool TroopCard::position_meeting(sf::Vector2f position) {
    float dx = position.x - _position.x;
    float dy = position.y - _position.y;

    // colisao em forma de quadrado por enquanto
    return (0 <= dx && dx <= _width && 0 <= dy && dy <= _width);
}

void TroopCard::draw() {
    sf::RectangleShape rect(sf::Vector2f(_width, _width));
    rect.setPosition(_position);

    sf::Color colors[TROOP_COUNT] = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta,
        sf::Color::Yellow, sf::Color::White, sf::Color::Cyan};

    rect.setFillColor(_texture ? sf::Color(0, 0, 0, 100) : colors[_troop]);
    _room.get_window().draw(rect);

    // desenhando o sprite
    if (_texture) {
        sf::RectangleShape sprite(sf::Vector2f(_width, _width));
        sprite.setPosition(_position);
        sprite.setTexture(_texture);

        _room.get_window().draw(sprite);
    }

    // desenhando o preco
    std::stringstream s;
    s << _price;

    sf::Text price_text(s.str(), GameManager::get_instance().get_font(), 30);
    price_text.setPosition(_position + sf::Vector2f(30, _width - 20));

    _room.get_window().draw(price_text);
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