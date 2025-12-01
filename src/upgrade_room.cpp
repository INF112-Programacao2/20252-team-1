#include "upgrade_room.h"
#include "game_manager.h"
#include "game_room.h"
#include "globals.h"
#include "room_manager.h"
#include "wall.h"
#include <iostream>
#include <cmath>

UpgradeRoom::UpgradeRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager),
      _upgrades{
          UpgradeUI(
              "Ponto Fraco",                                            // Nome
              1000,                                                      // Preço
              2000,                                                      // Incremento do preço
              0,                                                        // Nivel atual
              3,                                                        // Nivel maximo
              "Aumenta o dano geral que os inimigos levam em 10%",      // Descricao
              sf::Vector2f(75, 170),                                    // Posicao
              *this,                                                    // Room

              []() { // Funcao do upgrade
                  GameManager &gm = GameManager::get_instance();
                  double atual = gm.get_damage_multiplier();

                  gm.set_damage_multiplier(atual + 0.10);
              }),
          UpgradeUI(
              "Ataque Rapido",                                   // Nome
              300,                                               // Preço
              600,                                               // Incremento do preço
              0,                                                 // Nivel atual
              5,                                                 // Nivel máximo
              "Reduz o tempo base de recarga das tropas em 10%", // Descricao
              sf::Vector2f(375, 170),                            // Posição
              *this,                                             // Room

              []() { // Funcao do upgrade
                  GameManager &gm = GameManager::get_instance();

                  double novo_cooldown = gm.get_cooldown_multiplier() - 0.1;
                  if (gm.get_cooldown_multiplier() - 0.1 < 0.1)
                      novo_cooldown = 0.1; // Limite minimo de cooldown so para garantir

                  gm.set_cooldown_multiplier(novo_cooldown);
              }),
          UpgradeUI(
              "Mais Vida",
              400,
              800,
              0,
              8,
              "Aumenta a vida maxima e a vida atual do muro em 250",
              sf::Vector2f(675, 170),
              *this,

              []() {
                  GameManager &gm = GameManager::get_instance();

                  Wall &wall = gm.get_game_room().get_wall();
                  wall.increase_max_life(250);
                  wall.increase_life(250);
              }),
          UpgradeUI(
              "Espinhos",
              500,
              400,
              0,
              3,
              "Agora o muro tem espinhos! Sempre que um inimigo causar dano no muro, este inimigo vai receber dano dos espinhos. +10 de dano por nivel",
              sf::Vector2f(975, 170),
              *this,

              []() {
                  GameManager &gm = GameManager::get_instance();
                  Wall &wall = gm.get_game_room().get_wall();
                  wall.increase_spike_damage(10);
              }),
          UpgradeUI(
              "Investidor",
              1000,
              5000,
              0,
              5,
              "Aumenta o ganho total de pontos de todas as fontes em 10%",
              sf::Vector2f(1275, 170),
              *this,

              []() {
                  GameManager &gm = GameManager::get_instance();
                  double atual = gm.get_point_multiplier();
                  gm.set_point_multiplier(atual + 0.10);
              }),
          UpgradeUI(
              "Tropas Fortes", 
              400,
              1200,
              0,
              5,
              "Aumenta o dano causado pelas tropas em 15%", 
              sf::Vector2f(1575, 170),
              *this,
              []() {
                  GameManager &gm = GameManager::get_instance();
                  double atual = gm.get_troop_damage_multiplier();
                  gm.set_troop_damage_multiplier(atual + 0.15); 
              }),
          UpgradeUI(
              "Tiro preciso", 
              800,
              1600,
              0,
              5,
              "As tropas tem +10% de chance de causar o dobro de dano", 
              sf::Vector2f(75, 570),
              *this, 
              []() { 
                  GameManager &gm = GameManager::get_instance();
                  int atual = gm.get_crit_chance();
                  gm.set_crit_chance(atual + 10); 
              }),
      } {

    if (!_hud_background.loadFromFile("assets/hud.png")) {
        std::cerr << "Erro abrindo asset da HUD!\n";
        std::exit(1);
    }

    _hud_background.setRepeated(true);
}

UpgradeRoom::~UpgradeRoom() = default;

void UpgradeRoom::start() {
    // Inicializacao do UpgradeRoom
}

void UpgradeRoom::run(double dt, const std::vector<sf::Event> &event_queue) {
    for (const sf::Event &event : event_queue) {

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _paused = !_paused;

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
                _room_manager.rollback_room();
        }
    }

    _window.clear(sf::Color(50, 150, 50));

    sf::Text points_text(
        "Pontos: " + std::to_string(GameManager::get_instance().get_points()), (GameManager::get_instance().get_font()), 40);

    points_text.setPosition(
        sf::Vector2f(DESKTOP_SIZE.x - points_text.getGlobalBounds().width - 50, 50));

    // HUD
    sf::Sprite hud_rect(_hud_background);
    hud_rect.setTextureRect(sf::IntRect(0, 0, DESKTOP_SIZE.x, _hud_background.getSize().y));
    hud_rect.scale(1.2, 1.2);
    _window.draw(hud_rect);

    // Upgrades
    for (auto &upgrade : _upgrades) {
        if (!_paused) {
            upgrade.run(dt, event_queue);
        }
        upgrade.draw();
    }

    _window.draw(points_text);

    if (_paused) {
        // menu de pausa na upgrade room
        sf::RectangleShape pause_rect((sf::Vector2f)DESKTOP_SIZE);
        pause_rect.setFillColor(sf::Color(0, 0, 0, 150));
        _window.draw(pause_rect);

        sf::Font& font = GameManager::get_instance().get_font();
        sf::Text pause_text("JOGO PAUSADO", font, 80);
        pause_text.setFillColor(sf::Color::White);
        sf::FloatRect bounds = pause_text.getLocalBounds();
        pause_text.setOrigin(bounds.width / 2, bounds.height / 2);
        pause_text.setPosition(DESKTOP_SIZE.x / 2, DESKTOP_SIZE.y / 2 - 150);
        _window.draw(pause_text);

        TextButton option_1("Continuar", font, 50, [this]() { this->_paused = false; }, *this);
        option_1.center();
        option_1.offset_position(sf::Vector2f(0, -30));
        option_1.run(event_queue);

        TextButton option_2("Voltar ao menu", font, 50, [this]() {
            this->_paused = false;
            _room_manager.change_room("main_menu");
            }, *this);
        option_2.center();
        option_2.offset_position(sf::Vector2f(0, 70));
        option_2.run(event_queue);

        TextButton option_3("Salvar e Sair", font, 50, [this]() { this->_window.close(); }, *this);
        option_3.center();
        option_3.offset_position(sf::Vector2f(0, 170));
        option_3.run(event_queue);

        option_1.draw();
        option_2.draw();
        option_3.draw();
    }

    _window.display();
}

void UpgradeRoom::end() {
    for (auto &upgrade : _upgrades)
        upgrade.reset_feedback();
}

std::array<int, UPGRADE_COUNT> UpgradeRoom::get_upgrade_levels() const {
    std::array<int, UPGRADE_COUNT> result;
    for (int i = 0; i < UPGRADE_COUNT; i++)
        result[i] = _upgrades[i].get_level();

    return result;
}

void UpgradeRoom::set_upgrade_levels(std::array<int, UPGRADE_COUNT> levels) {
    for (int i = 0; i < UPGRADE_COUNT; i++) {
        _upgrades[i].set_level(levels[i]);
    }
}