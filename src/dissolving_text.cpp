#include "dissolving_text.h"

DissolvingText::DissolvingText(sf::Vector2f position, double dissolving_time, Room &room)
    : _position(position), _dissolving_time(dissolving_time), _room(room) {}

DissolvingText::DissolvingText(sf::Text text, sf::Vector2f position, double dissolving_time, Room &room)
    : _text(text), _position(position), _dissolving_time(dissolving_time), _room(room) {}

void DissolvingText::run(double dt) {
    _clock.update(dt);

    // move pra cima
    const double speed = -30;
    _position.y += speed * dt;

    if (_clock.get_seconds_elapsed() > _dissolving_time)
        _hidden = true;
}

void DissolvingText::draw() {
    if (_hidden)
        return;

    // muda a opacidade com o tempo
    sf::Color new_color = _text.getFillColor();
    new_color.a = 255 * (1.0 - _clock.get_seconds_elapsed() / _dissolving_time);

    _text.setFillColor(new_color);
    _text.setPosition(_position);
    _room.get_window().draw(_text);
}

void DissolvingText::set_text(sf::Text text) {
    _text = text;
}

void DissolvingText::set_string(std::string str) {
    _text.setString(str);
}

void DissolvingText::set_position(sf::Vector2f position) {
    _position = position;
}

void DissolvingText::restart() {
    _hidden = false;
    _clock.restart();
}