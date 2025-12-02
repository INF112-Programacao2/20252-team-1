#include "credits_room.h"
#include "game_manager.h"
#include "room_manager.h"
#include <stdexcept>

CreditsRoom::CreditsRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager),
      _font(GameManager::get_instance().get_font()) {

    // carregando titulo
    if (!_title_texture.loadFromFile("assets/deneter.png")) {
        throw std::runtime_error("Erro ao carregar asset do titulo (assets/deneter.png)");
    }
    _title_sprite.setTexture(_title_texture);

    // centraliza o titulo no topo
    sf::FloatRect title_bounds = _title_sprite.getLocalBounds();
    _title_sprite.setOrigin(title_bounds.left + title_bounds.width / 2.0f,
                            title_bounds.top + title_bounds.height / 2.0f);
    _title_sprite.setPosition(static_cast<float>(window.getSize().x) / 2.0f, 200.0f);

    if (!_background_texture.loadFromFile("assets/creditos.png")) {
        throw std::runtime_error("Erro ao carregar asset de background (assets/creditos.png)");
    }
    _background_sprite.setTexture(_background_texture);

    // ajustador de escala
    sf::Vector2u window_size = window.getSize();
    sf::Vector2u texture_size = _background_texture.getSize();
    float scale_x = static_cast<float>(window_size.x) / texture_size.x;
    float scale_y = static_cast<float>(window_size.y) / texture_size.y;
    _background_sprite.setScale(scale_x, scale_y);

    if (!_arrow_texture.loadFromFile("assets/left arrow.png")) {
        throw std::runtime_error("Erro ao carregar asset da seta (assets/left arrow.png)");
    }
    _arrow_sprite.setTexture(_arrow_texture);

    _arrow_sprite.setScale(0.25f, 0.25f);

    _arrow_sprite.setPosition(10.f, 10.f);

    // texto dos creditos
    _credits_text.setFont(_font);
    _credits_text.setString("Desenvolvido por:");
    _credits_text.setCharacterSize(60);
    _credits_text.setFillColor(sf::Color::White);
    _credits_text.setOutlineColor(sf::Color::Black);
    _credits_text.setOutlineThickness(2.0f);

    sf::FloatRect header_bounds = _credits_text.getLocalBounds();
    _credits_text.setOrigin(header_bounds.left + header_bounds.width / 2.0f,
                            header_bounds.top + header_bounds.height / 3.0f);
    _credits_text.setPosition(static_cast<float>(window.getSize().x) / 2.0f, 400.0f);

    _names_text.setFont(_font);
    _names_text.setString("Davi Aziz Santos Salazar\n\nDavi Nobre Oliveira\n\nEnzo de Freitas Alencar\n\nGabriel Silverio Tavares\n\nPedro Henrique Carvalho Martins");
    _names_text.setCharacterSize(30);
    _names_text.setFillColor(sf::Color::White);
    _names_text.setOutlineColor(sf::Color::Black);
    _names_text.setOutlineThickness(2.0f);

    sf::FloatRect names_bounds = _names_text.getLocalBounds();
    _names_text.setOrigin(names_bounds.left + names_bounds.width / 2.0f,
                          names_bounds.top + names_bounds.height / 3.0f);
    _names_text.setPosition(static_cast<float>(window.getSize().x) / 2.0f, 650.0f);
}

void CreditsRoom::change_room(std::string room_name) {
    _room_manager.change_room(room_name);
}

void CreditsRoom::start() {
    GameManager::get_instance().play_menu_music();
}

void CreditsRoom::run(double _dt, const std::vector<sf::Event> &event_queue) {
    sf::Vector2i mouse_pos = get_mouse_position();
    bool is_hovering = _arrow_sprite.getGlobalBounds().contains((sf::Vector2f)mouse_pos);

    for (const sf::Event &event : event_queue) {
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left &&
            is_hovering) {

            this->change_room("main_menu");
        }
    }

    draw();
}

void CreditsRoom::draw() {
    get_window().clear(sf::Color::Black);

    _window.draw(_background_sprite);
    _window.draw(_title_sprite);
    _window.draw(_credits_text);
    _window.draw(_names_text);

    // efeito hover pro botao da seta
    sf::Vector2i mouse_pos = get_mouse_position();
    if (_arrow_sprite.getGlobalBounds().contains((sf::Vector2f)mouse_pos)) {
        _arrow_sprite.setColor(sf::Color(150, 150, 150));
    } else {
        _arrow_sprite.setColor(sf::Color::White);
    }

    _window.draw(_arrow_sprite);

    get_window().display();
}