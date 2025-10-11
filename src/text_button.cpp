#include <iostream>
#include "text_button.h"
#include "globals.h"

TextButton::TextButton(std::string text, sf::Font &font, int font_size, Room &room)
    : _room(room) {
    _draw_text.setString(text);
    _draw_text.setFont(font);
    _draw_text.setCharacterSize(font_size);
}

TextButton::TextButton(std::string text, sf::Font &font, int font_size,
                       std::function<void()> on_click_callback, Room &room)
    : TextButton(text, font, font_size, room) {
    _on_click_callback = std::move(on_click_callback);
}

sf::Vector2f TextButton::get_position() {
    return _position;
}

void TextButton::set_position(sf::Vector2f position) {
    _position = position;
}

void TextButton::offset_position(sf::Vector2f offset) {
    _position += offset;
}

void TextButton::center() {
    sf::Vector2f offset(_draw_text.getLocalBounds().width * .5, 0);
    _position = (sf::Vector2f)DESKTOP_SIZE * .5f - offset;
}

void TextButton::run(const std::vector<sf::Event> &event_queue) {
    for (const sf::Event &event : event_queue) {
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left &&
            position_meeting(_room.get_mouse_position()) &&
            _on_click_callback) {
            _on_click_callback();
        }
    }
}

void TextButton::draw() {
    sf::Color normal = sf::Color::White;
    sf::Color hover(150, 150, 150);
    _draw_text.setFillColor(position_meeting(_room.get_mouse_position()) ? hover : normal);

    _draw_text.setPosition(_position);
    _room.get_window().draw(_draw_text);
}

bool TextButton::position_meeting(sf::Vector2i position) {
    _draw_text.setPosition(_position);
    return _draw_text.getGlobalBounds().contains((sf::Vector2f)position);
}