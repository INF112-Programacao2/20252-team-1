#include "volume_controller.h"
#include "game_manager.h"

const float gap = 25;
const float s_size = 50;
const float bar_width = 300;
sf::Rect<float> plus_rect(DESKTOP_SIZE.x - s_size - 2 * gap, DESKTOP_SIZE.y - 125, s_size, s_size);
sf::Rect<float> minus_rect(DESKTOP_SIZE.x - 3 * s_size - 4 * gap - bar_width, DESKTOP_SIZE.y - 125, s_size, s_size);

VolumeController::VolumeController(Room &room) : _room(room) {
    if (!_plus_icon.loadFromFile("assets/mais.png")) {
        throw std::runtime_error("Erro abrindo icone de mais (assets/mais.png)");
    }
    if (!_minus_icon.loadFromFile("assets/menos.png")) {
        throw std::runtime_error("Erro abrindo icone de menos (assets/minus.png)");
    }
    if (!_volume_icon.loadFromFile("assets/volume.png")) {
        throw std::runtime_error("Erro abrindo icone do volume (assets/volume.png)");
    }
}

void VolumeController::run(const std::vector<sf::Event> &event_queue) {
    bool pressed = false;
    for (const sf::Event &event : event_queue) {
        pressed = (event.type == sf::Event::MouseButtonPressed &&
                   event.mouseButton.button == sf::Mouse::Left);
    }

    _minus_hover = _plus_hover = false;
    if (minus_rect.contains((sf::Vector2f)_room.get_mouse_position())) {
        _minus_hover = true;
        if (pressed)
            GameManager::get_instance().decrease_volume(10);
    } else if (plus_rect.contains((sf::Vector2f)_room.get_mouse_position())) {
        _plus_hover = true;
        if (pressed)
            GameManager::get_instance().increase_volume(10);
    }
}

void VolumeController::draw() {
    sf::RectangleShape minus_sprite({s_size, s_size});
    sf::RectangleShape volume_sprite({s_size, s_size});
    sf::RectangleShape plus_sprite({s_size, s_size});

    minus_sprite.setTexture(&_minus_icon);
    volume_sprite.setTexture(&_volume_icon);
    plus_sprite.setTexture(&_plus_icon);

    minus_sprite.setPosition(minus_rect.getPosition());
    minus_sprite.setFillColor(_minus_hover ? sf::Color(150, 150, 150) : sf::Color::White);
    _room.get_window().draw(minus_sprite);

    volume_sprite.setPosition(minus_rect.getPosition() + sf::Vector2f(s_size + gap, 0));
    _room.get_window().draw(volume_sprite);

    // desenha barra de volume
    float t = GameManager::get_instance().get_music_volume() / 100.f;

    sf::RectangleShape volume_bar_bg({bar_width, 30});
    sf::RectangleShape volume_bar_fg({bar_width * t, 30});

    volume_bar_bg.setPosition({DESKTOP_SIZE.x - s_size - bar_width - 3 * gap, DESKTOP_SIZE.y - 115});
    volume_bar_fg.setPosition(volume_bar_bg.getPosition());

    volume_bar_bg.setFillColor(sf::Color(100, 100, 100));
    volume_bar_fg.setFillColor(sf::Color::White);

    _room.get_window().draw(volume_bar_bg);
    _room.get_window().draw(volume_bar_fg);

    plus_sprite.setPosition(plus_rect.getPosition());
    plus_sprite.setFillColor(_plus_hover ? sf::Color(150, 150, 150) : sf::Color::White);
    _room.get_window().draw(plus_sprite);
}