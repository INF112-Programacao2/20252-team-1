#include <iostream>
#include "game_room.h"
#include "globals.h"
#include "text_button.h"
#include "game_manager.h"

GameRoom::GameRoom(sf::RenderWindow &window)
    : Room(window), _troop_manager(*this) {
    // carrega a fonte pra ser usada nos menus
    if (!_font.loadFromFile("assets/Minecraftia-Regular.ttf")) {
        std::cerr << "***\nNao foi possivel encontrar a fonte em \""
                  << "assets/Minecraftia-Regular.ttf"
                  << "\"\n***" << std::endl;

        std::exit(0);
    }
}

GameRoom::~GameRoom() = default;

void GameRoom::start() {}

void GameRoom::run(double dt, const std::vector<sf::Event> &event_queue) {
    //* rodando:
    for (const sf::Event &event : event_queue) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _paused = !_paused;
    }

    if (!_paused)
        _troop_manager.run(dt, event_queue);
    else
        _troop_manager.pause();

    //* desenhando:
    _window.clear(sf::Color(50, 150, 50));

    _troop_manager.draw();

    sf::Text points_text(
        "Pontos: " + std::to_string(GameManager::get_instance().get_points()), _font, 40);

    points_text.setPosition(
        sf::Vector2f(DESKTOP_SIZE.x - points_text.getGlobalBounds().width - 50, 50));

    _window.draw(points_text);

    if (_paused) {
        // desenhando fundo preto do menu de pause
        sf::RectangleShape pause_rect((sf::Vector2f)DESKTOP_SIZE);
        pause_rect.setFillColor(sf::Color(0, 0, 0, 150));
        _window.draw(pause_rect);

        // criando botoes
        TextButton option_1("Continuar", _font, 50, [this]() { this->_paused = false; }, *this);
        option_1.center();
        option_1.offset_position(sf::Vector2f(0, -50));
        option_1.run(event_queue);

        TextButton option_2("Salvar e Sair", _font, 50, [this]() { this->_window.close(); }, *this);
        option_2.center();
        option_2.offset_position(sf::Vector2f(0, 50));
        option_2.run(event_queue);

        option_1.draw();
        option_2.draw();
    }

    _window.display();
}

void GameRoom::end() {}