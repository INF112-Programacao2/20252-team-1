#include "credits_room.h"
#include "game_manager.h"
#include "room_manager.h"
#include <iostream>  

CreditsRoom::CreditsRoom(sf::RenderWindow &window, RoomManager &room_manager): 
    Room(window, room_manager),
    _font(GameManager::get_instance().get_font()),
    _menu_button("Menu Principal", _font, 30, *this) {

    // titulo
    _title_text.setFont(_font);
    _title_text.setString("Creditos");
    _title_text.setCharacterSize(90);
    _title_text.setFillColor(sf::Color::White);
    sf::FloatRect title_bounds = _title_text.getLocalBounds();
    _title_text.setOrigin(title_bounds.left + title_bounds.width / 2.0f,
                          title_bounds.top + title_bounds.height / 2.0f);
    _title_text.setPosition(static_cast<float>(window.getSize().x) / 2.0f, 100.0f);

    // creditos
    _credits_text.setFont(_font);
    _credits_text.setString("Desenvolvido por:\n- Davi\n- Davi\n- Enzo\n- Gabriel\n- Pedro");
    _credits_text.setCharacterSize(30);
    _credits_text.setFillColor(sf::Color::White);
    sf::FloatRect credits_bounds = _credits_text.getLocalBounds();
    _credits_text.setOrigin(credits_bounds.left + credits_bounds.width / 2.0f,
                            credits_bounds.top + credits_bounds.height / 2.0f);
    _credits_text.setPosition(static_cast<float>(window.getSize().x) / 2.0f, 500.0f);

    // botao de menu
    _menu_button.center();
    _menu_button.offset_position(sf::Vector2f(0, 500));
    _menu_button.set_on_click_callback([this]() { this->change_room("main_menu"); });
}

void CreditsRoom::change_room(std::string room_name) {
    _room_manager.change_room(room_name);
}

void CreditsRoom::start() {
    // comeca musica do jogo
    GameManager::get_instance().play_game_music();
}

void CreditsRoom::run(double _dt, const std::vector<sf::Event> &event_queue) {
    _menu_button.run(event_queue);

    draw();
}

void CreditsRoom::draw() {
    std::cout << "Drawing Credits Room\n" << std::endl; //! DEBUG
    get_window().clear(sf::Color::Black);

    _window.draw(_title_text);
    _window.draw(_credits_text);

    _menu_button.draw();

    get_window().display();
}

