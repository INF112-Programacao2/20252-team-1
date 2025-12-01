#include <iostream>
#include <cmath>
#include "game_room.h"
#include "globals.h"
#include "text_button.h"
#include "game_manager.h"
#include "room_manager.h"
#include "visual_effect.h"

GameRoom::GameRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager),
      _troop_manager(*this),
      _wave_manager(*this),
      _font(GameManager::get_instance().get_font()),
      _wall(1000, 0, *this) {

    GameManager::get_instance().set_game_room(this);
    if (!Wall::load_texture("assets/muro.png")) {
        std::cerr << "Erro abrindo asset do muro!\n";
        std::exit(1);
    }

    if (!_background.loadFromFile("assets/background.png")) {
        std::cerr << "Erro abrindo asset do background!\n";
        std::exit(1);
    }
    if (!_background2.loadFromFile("assets/background22.png")) {
        std::cerr << "Erro abrindo asset do background2!\n";
        std::exit(1);
    }

    if (!_hud_background.loadFromFile("assets/hud.png")) {
        std::cerr << "Erro abrindo asset da HUD!\n";
        std::exit(1);
    }

    _background.setRepeated(true);
    _background2.setRepeated(true);
    _hud_background.setRepeated(true);
}

GameRoom::~GameRoom() = default;

void GameRoom::start() {}

void GameRoom::run(double dt, const std::vector<sf::Event> &event_queue) {
    // variavel para verificar se o jogo acabou
    _game_over = _wall.game_over();

    //* rodando:
    for (const sf::Event &event : event_queue) {
        // ESC pausa
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _paused = !_paused;

            if (event.key.code == sf::Keyboard::Tab)
                _room_manager.change_room("upgrade");
        }
    }

    if (!_paused && !_game_over) {
        _troop_manager.run(dt, event_queue);
        _wave_manager.run(dt);
        _wall.run(dt);

        // atualizando efeitos visuais
        for (int i = 0; i < _visual_effects.size();) {
            _visual_effects[i]->run(dt);

            if (_visual_effects[i]->is_finished()) {
                std::swap(_visual_effects[i], _visual_effects.back());
                _visual_effects.pop_back();
            }
            else {
                i++;
            }
        }
    }

    //* desenhando:
    _window.clear();

    sf::Sprite bg(_background);
    bg.setPosition({0, HUD_HEIGHT});
    bg.setTextureRect(sf::IntRect(0, 0, WALL_POSITION_X, DESKTOP_SIZE.y - HUD_HEIGHT));
    _window.draw(bg);

    sf::Sprite bg2(_background2);
    bg2.setPosition({WALL_POSITION_X, HUD_HEIGHT});
    bg2.setTextureRect(sf::IntRect(0, 0, GAME_SIZE_X - WALL_POSITION_X, DESKTOP_SIZE.y - HUD_HEIGHT));
    _window.draw(bg2);

    _wall.draw();
    _wave_manager.draw();
    _troop_manager.draw();

    // desenhando efeitos visuais (desenha por cima de tudo no campo, mas abaixo da HUD)
    for (auto& effect : _visual_effects) {
        effect->draw();
    }

    // HUD
    sf::Sprite hud_rect(_hud_background);
    hud_rect.setTextureRect(sf::IntRect(0, 0, DESKTOP_SIZE.x, _hud_background.getSize().y));
    hud_rect.scale(1.2, 1.2);
    _window.draw(hud_rect);
    _wall.draw_wall_health_bar();

    // UI de pontos:
    sf::Text points_text(
        "Pontos: " + std::to_string(GameManager::get_instance().get_points()), _font, 40);

    points_text.setPosition(
        sf::Vector2f(DESKTOP_SIZE.x - points_text.getGlobalBounds().width - 50, 50));

    _window.draw(points_text);

    // logica de vitoria
    if (_wave_manager.is_completed()) {
        sf::RectangleShape win_rect((sf::Vector2f)DESKTOP_SIZE);
        win_rect.setFillColor(sf::Color(0, 0, 0, 200));
        _window.draw(win_rect);

        sf::Text win_text("VOCE VENCEU!", _font, 100);
        win_text.setFillColor(sf::Color::Green);
        sf::FloatRect bounds = win_text.getLocalBounds();
        win_text.setOrigin(bounds.width / 2, bounds.height / 2);
        win_text.setPosition(DESKTOP_SIZE.x / 2, DESKTOP_SIZE.y / 2 - 100);
        _window.draw(win_text);

        TextButton option_1("Voltar ao menu", _font, 50, [this]() {
            _room_manager.change_room("main_menu");
            }, *this);
        option_1.center();
        option_1.offset_position(sf::Vector2f(0, 50));
        option_1.run(event_queue);

        TextButton option_2("Sair", _font, 50, [this]() { this->_window.close(); }, *this);
        option_2.center();
        option_2.offset_position(sf::Vector2f(0, 150));
        option_2.run(event_queue);

        option_1.draw();
        option_2.draw();
    }
    else if( _game_over) {
        sf::RectangleShape gameover_rect((sf::Vector2f)DESKTOP_SIZE);
        gameover_rect.setFillColor(sf::Color(0, 0, 0, 200));
        _window.draw(gameover_rect);

        sf::Text gameover_text("GAME OVER", _font, 100);
        gameover_text.setFillColor(sf::Color::Red);
        gameover_text.setPosition(
            sf::Vector2f((DESKTOP_SIZE.x - gameover_text.getGlobalBounds().width) / 2,
                         (DESKTOP_SIZE.y - gameover_text.getGlobalBounds().height) / 2 - 50));
        _window.draw(gameover_text);

        // botoes do game_over
        TextButton option_1("Voltar ao menu", _font, 50, [this]() { _room_manager.change_room("main_menu"); 
                                                                    _game_over = false; }, *this);
        option_1.center();
        option_1.offset_position(sf::Vector2f(0, 50));
        option_1.run(event_queue);

        TextButton option_2("Sair", _font, 50, [this]() { this->_window.close(); }, *this);
        option_2.center();
        option_2.offset_position(sf::Vector2f(0, 150));
        option_2.run(event_queue);

        option_1.draw();
        option_2.draw();
    }

    else if (_paused) {
        // desenhando fundo preto do menu de pause
        sf::RectangleShape pause_rect((sf::Vector2f)DESKTOP_SIZE);
        pause_rect.setFillColor(sf::Color(0, 0, 0, 150));
        _window.draw(pause_rect);

        sf::Text pause_text("JOGO PAUSADO", _font, 80);
        pause_text.setFillColor(sf::Color::White);
        sf::FloatRect bounds = pause_text.getLocalBounds();
        pause_text.setOrigin(bounds.width / 2, bounds.height / 2);
        pause_text.setPosition(DESKTOP_SIZE.x / 2, DESKTOP_SIZE.y / 2 - 150);
        _window.draw(pause_text);

        TextButton option_1("Continuar", _font, 50, [this]() { this->_paused = false; }, *this);
        option_1.center();
        option_1.offset_position(sf::Vector2f(0, -30)); 
        option_1.run(event_queue);

        TextButton option_2("Voltar ao menu", _font, 50, [this]() {
            this->_paused = false;
            _room_manager.change_room("main_menu");
            }, *this);
        option_2.center();
        option_2.offset_position(sf::Vector2f(0, 70));
        option_2.run(event_queue);

        TextButton option_3("Salvar e Sair", _font, 50, [this]() {
            this->_window.close();
            }, *this);
        option_3.center();
        option_3.offset_position(sf::Vector2f(0, 170));
        option_3.run(event_queue);

        option_1.draw();
        option_2.draw();
        option_3.draw();
    }

    // !DEBUG (MOSTRA FRAMERATE)
    sf::Text fps(std::to_string(round(1.0 / dt)).substr(0, 5), _font, 30);
    fps.setPosition(sf::Vector2f(50, 50));
    _window.draw(fps);

    _window.display();
}

void GameRoom::end() {}

void GameRoom::add_effect(std::unique_ptr<VisualEffect> effect) {
    _visual_effects.push_back(std::move(effect));
}

TroopManager &GameRoom::get_troop_manager() {
    return _troop_manager;
}

WaveManager &GameRoom::get_wave_manager() {
    return _wave_manager;
}

Wall &GameRoom::get_wall() {
    return _wall;
}