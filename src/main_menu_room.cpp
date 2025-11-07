#include "main_menu_room.h"
#include "game_manager.h"
#include "room_manager.h"
#include <iostream> //! DEBUG

const int font_size = 50;

MainMenuRoom::MainMenuRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager),
      _font(GameManager::get_instance().get_font()),
      _start_button("Iniciar", _font, font_size, *this),
      _credits_button("Creditos", _font, font_size, *this),
      _exit_button("Sair", _font, font_size, *this) {

    // centraliza os botoes
    _start_button.center();
    _credits_button.center();
    _exit_button.center();

    // espaca eles verticalmente
    _start_button.offset_position(sf::Vector2f(0, -150));
    _credits_button.offset_position(sf::Vector2f(0, 50));
    _exit_button.offset_position(sf::Vector2f(0, 150));

    // TODO: adiciona os callbacks
    _start_button.set_on_click_callback([this]() { this->change_room("game"); });
    _credits_button.set_on_click_callback([]() { std::cout << "Creditos\n"; });
    _exit_button.set_on_click_callback([this]() { this->get_window().close(); });
}

void MainMenuRoom::change_room(std::string room_name) {
    _room_manager.change_room(room_name);
}

void MainMenuRoom::run(double _dt, const std::vector<sf::Event> &event_queue) {
    _start_button.run(event_queue);
    _credits_button.run(event_queue);
    _exit_button.run(event_queue);

    draw();
}

void MainMenuRoom::draw() {
    get_window().clear(sf::Color(20, 20, 100));

    _start_button.draw();
    _credits_button.draw();
    _exit_button.draw();

    get_window().display();
}