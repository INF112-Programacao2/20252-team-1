#include "main_menu_room.h"
#include "game_manager.h"
#include "room_manager.h"
#include <stdexcept>

const int font_size = 50;

MainMenuRoom::MainMenuRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager),
      _font(GameManager::get_instance().get_font()),
      _continue_button("Continuar Jogo", _font, font_size, *this),
      _new_game_button("Novo Jogo", _font, font_size, *this),
      _tutorial_button("Tutorial", _font, font_size, *this),
      _credits_button("Creditos", _font, font_size, *this),
      _exit_button("Sair", _font, font_size, *this),
      _volume_controller(*this) {

    // Carregando Textura do Titulo
    if (!_title_texture.loadFromFile("assets/deneter.png")) {
        throw std::runtime_error("Erro ao carregar asset do titulo (assets/deneter.png)");
    }
    _title_sprite.setTexture(_title_texture);

    // Centraliza o titulo e coloca um pouco acima dos botoes
    sf::FloatRect title_bounds = _title_sprite.getLocalBounds();
    _title_sprite.setOrigin(title_bounds.left + title_bounds.width / 2.0f,
                            title_bounds.top + title_bounds.height / 2.0f);

    // Posiciona no meio da tela horizontalmente, e deslocado para cima verticalmente
    _title_sprite.setPosition(window.getSize().x / 2.0f, 200.f);

    // centraliza os botoes
    _continue_button.center();
    _new_game_button.center();
    _tutorial_button.center();
    _credits_button.center();
    _exit_button.center();

    // espaca eles verticalmente
    _continue_button.offset_position(sf::Vector2f(0, -100));
    _new_game_button.offset_position(sf::Vector2f(0, 0));
    _tutorial_button.offset_position(sf::Vector2f(0, 100));
    _credits_button.offset_position(sf::Vector2f(0, 200));
    _exit_button.offset_position(sf::Vector2f(0, 300));

    // callbacks
    _continue_button.set_on_click_callback([this]() { this->change_room("game", true); });
    _new_game_button.set_on_click_callback([this]() { this->change_room("game", false); });
    _tutorial_button.set_on_click_callback([this]() {});
    _credits_button.set_on_click_callback([this]() { this->change_room("Creditos", false); });
    _exit_button.set_on_click_callback([this]() { this->get_window().close(); });
}

void MainMenuRoom::start() {
    // comeca musica do menu
    GameManager::get_instance().play_menu_music();
}

void MainMenuRoom::change_room(std::string room_name, bool load_save) {
    if (load_save)
        GameManager::get_instance().get_game_saver()->load();
    else
        GameManager::get_instance().get_game_saver()->new_game();

    _room_manager.change_room(room_name);
}

void MainMenuRoom::run(double _dt, const std::vector<sf::Event> &event_queue) {
    _continue_button.run(event_queue);
    _new_game_button.run(event_queue);
    _tutorial_button.run(event_queue);
    _credits_button.run(event_queue);
    _exit_button.run(event_queue);

    _volume_controller.run(event_queue);

    draw();
}

void MainMenuRoom::draw() {
    get_window().clear(sf::Color(20, 20, 100));

    // Desenha o titulo
    _window.draw(_title_sprite);

    _continue_button.draw();
    _new_game_button.draw();
    _tutorial_button.draw();
    _credits_button.draw();
    _exit_button.draw();

    _volume_controller.draw();

    get_window().display();
}