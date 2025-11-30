#include <SFML/Graphics.hpp>
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

    rect.setFillColor(sf::Color(0, 0, 0, 100));
    _room.get_window().draw(rect);

    // desenhando o sprite
    if (_texture) {
        rect.setFillColor(sf::Color::White);
        rect.setTexture(_texture);

        _room.get_window().draw(rect);
    }

    // overlay de hover
    rect.setTexture(0);
    if (position_meeting((sf::Vector2f)_room.get_mouse_position())) {
        rect.setFillColor(sf::Color(0, 0, 0, 50));
        _room.get_window().draw(rect);
    }

    // desenhando o preco e o fundo dele
    sf::Text price_text(
        std::to_string(_price), GameManager::get_instance().get_font(), 30);
    price_text.setPosition(_position + sf::Vector2f(30, _width - 20));

    sf::FloatRect bounds = price_text.getGlobalBounds();

    const float padding = 5;
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(bounds.getPosition() - sf::Vector2f(padding, padding));
    rect.setSize(sf::Vector2f(bounds.width + 2 * padding, bounds.height + 2 * padding));

    _room.get_window().draw(rect);
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