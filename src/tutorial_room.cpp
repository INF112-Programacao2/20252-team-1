#include "tutorial_room.h"
#include "room_manager.h"
#include "globals.h"
#include <cmath>
#include <string>
#include <stdexcept>

TutorialRoom::TutorialRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager) {

    for (int i = 1; i <= SLIDE_COUNT; i++) {
        std::string path = "assets/tutorial" + std::to_string(i) + ".png";
        if (!_slides[i - 1].loadFromFile(path)) {
            throw std::runtime_error("Erro abrindo asset do tutorial (" + path + ")");
        }
    }

    if (!_arrow_texture.loadFromFile("assets/left arrow.png")) {
        throw std::runtime_error("Erro ao carregar asset da seta (assets/left arrow.png)");
    }

    _current_slide.setSize((sf::Vector2f)DESKTOP_SIZE);
    _current_slide.setTexture(&_slides[0]);

    _return_arrow.setTexture(_arrow_texture);
    _return_arrow.setScale(0.25f, 0.25f);
    _return_arrow.setPosition(10.f, 10.f);
}

void TutorialRoom::start() {
    _slide_idx = 0;
}

void TutorialRoom::run(double dt, const std::vector<sf::Event> &event_queue) {
    sf::Vector2i mouse_pos = get_mouse_position();
    bool is_hovering = _return_arrow.getGlobalBounds().contains((sf::Vector2f)mouse_pos);

    for (const sf::Event &event : event_queue) {
        bool clicked_button = event.type == sf::Event::MouseButtonReleased &&
                              event.mouseButton.button == sf::Mouse::Left &&
                              is_hovering;
        bool esc_pressed = event.type == sf::Event::KeyReleased &&
                           event.key.code == sf::Keyboard::Escape;

        if (clicked_button || esc_pressed) {
            _room_manager.rollback_room();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                // volta o slide
                _slide_idx = std::max(0, _slide_idx - 1);
                _current_slide.setTexture(&_slides[_slide_idx]);
            } else if (event.key.code == sf::Keyboard::Right) {
                // avanca o slide
                _slide_idx = std::min(SLIDE_COUNT - 1, _slide_idx + 1);
                _current_slide.setTexture(&_slides[_slide_idx]);
            }
        }
    }

    // volta
    _slide_idx = std::max(0, _slide_idx - 1);
    _current_slide.setTexture(&_slides[_slide_idx]);
    // avanca
    _slide_idx = std::min(SLIDE_COUNT - 1, _slide_idx + 1);
    _current_slide.setTexture(&_slides[_slide_idx]);

    draw();
}

void TutorialRoom::draw() {
    _window.clear();

    // slide atual
    _window.draw(_current_slide);

    // setinhas pra controlar o slide:
    bool hover_left = _left_arrow.getGlobalBounds().contains((sf::Vector2f)get_mouse_position());
    bool hover_left = _left_arrow.getGlobalBounds().contains((sf::Vector2f)get_mouse_position());

    // botao de voltar para menu principal:
    bool hover = _return_arrow.getGlobalBounds().contains((sf::Vector2f)get_mouse_position());
    _return_arrow.setColor(hover ? sf::Color(150, 150, 150) : sf::Color::White);

    _window.draw(_return_arrow);

    _window.display();
}