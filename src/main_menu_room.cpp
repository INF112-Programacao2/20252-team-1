#include "main_menu_room.h"
#include "game_manager.h"
#include "room_manager.h"
#include <iostream> //! DEBUG

const int font_size = 50;

MainMenuRoom::MainMenuRoom(sf::RenderWindow &window, RoomManager &room_manager, GameSaver &game_saver)
    : Room(window, room_manager),
      _font(GameManager::get_instance().get_font()),
      _continue_button("Continuar Jogo", _font, font_size, *this),
      _new_game_button("Novo Jogo", _font, font_size, *this),
      _tutorial_button("Tutorial", _font, font_size, *this),
      _credits_button("Creditos", _font, font_size, *this),
      _exit_button("Sair", _font, font_size, *this),
      _game_saver(game_saver) {

    // centraliza os botoes
    _continue_button.center();
    _new_game_button.center();
    _tutorial_button.center();
    _credits_button.center();
    _exit_button.center();

    // espaca eles verticalmente
    _continue_button.offset_position(sf::Vector2f(0, -200));
    _new_game_button.offset_position(sf::Vector2f(0, -100));
    _tutorial_button.offset_position(sf::Vector2f(0, 0));
    _credits_button.offset_position(sf::Vector2f(0, 100));
    _exit_button.offset_position(sf::Vector2f(0, 200));

    // TODO: adiciona os callbacks
    _continue_button.set_on_click_callback([this]() { this->change_room("game", true); });
    _new_game_button.set_on_click_callback([this]() { this->change_room("game", false); });
    _tutorial_button.set_on_click_callback([]() { std::cout << "Tutorial\n"; });
    _credits_button.set_on_click_callback([]() { std::cout << "Creditos\n"; });
    _exit_button.set_on_click_callback([this]() { this->get_window().close(); });
}

void MainMenuRoom::change_room(std::string room_name, bool load_save) {
    if (load_save)
        _game_saver.load();
    _room_manager.change_room(room_name);
}

void MainMenuRoom::run(double _dt, const std::vector<sf::Event> &event_queue) {
    _continue_button.run(event_queue);
    _new_game_button.run(event_queue);
    _tutorial_button.run(event_queue);
    _credits_button.run(event_queue);
    _exit_button.run(event_queue);

    draw();
}

void MainMenuRoom::draw() {
    get_window().clear(sf::Color(20, 20, 100));

    _continue_button.draw();
    _new_game_button.draw();
    _tutorial_button.draw();
    _credits_button.draw();
    _exit_button.draw();

    get_window().display();
}