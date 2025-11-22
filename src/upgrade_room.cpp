#include "upgrade_room.h"
#include "game_manager.h"
#include "globals.h"
#include <iostream>

UpgradeRoom::UpgradeRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager),
      _dano_bruto(
          "Dano Bruto",    // Nome
          100,              // Preço
          1,                // Nivel atual
		  5,				// Nivel maximo
          "Aumenta o multiplicador de dano das tropas em 0.25", // Descricao
          sf::Vector2f(80, 150), // Posicao
          *this,            // Room
          
          []() { // Funcao do upgrade
            GameManager& gm = GameManager::get_instance();
            double atual = gm.get_damage_multiplier();
              
            gm.set_damage_multiplier(atual + 0.25);
              
            std::cout << "Dano: x" << gm.get_damage_multiplier() << std::endl;
          }
      ),
	  _ataque_rapido(
          "Ataque Rapido", // Nome
          200,              // Preço
          1,                // Nivel atual
          5,                // Nivel máximo
          "Reduz o tempo de recarga das tropas em 0.1", // Descricao
          sf::Vector2f(380, 150), // Posição 
          *this,            // Room
          
          []() { // Funcao do upgrade
            GameManager& gm = GameManager::get_instance();
              
            double novo_cooldown = gm.get_cooldown_multiplier() - 0.1;
            if(gm.get_cooldown_multiplier() - 0.1 < 0.1)
				novo_cooldown = 0.1; // Limite minimo de cooldown so para garantir
              
            gm.set_cooldown_multiplier(novo_cooldown);
              
            std::cout << "Cooldown: x" << gm.get_cooldown_multiplier() << std::endl;
          }
      )
{}

UpgradeRoom::~UpgradeRoom() = default;

void UpgradeRoom::start() {
  	// Inicialização do UpgradeRoom
}

void UpgradeRoom::run(double dt, const std::vector<sf::Event> &event_queue) {
    _window.clear(sf::Color::Black);

    sf::Text points_text(
        "Pontos: " + std::to_string(GameManager::get_instance().get_points()), (GameManager::get_instance().get_font()), 40);

    points_text.setPosition(
        sf::Vector2f(DESKTOP_SIZE.x - points_text.getGlobalBounds().width - 50, 50));

    _window.draw(points_text);

    _dano_bruto.draw();
    _dano_bruto.run(dt, event_queue);
	_ataque_rapido.draw();
	_ataque_rapido.run(dt, event_queue);

    _window.display();
}

void UpgradeRoom::end() {
    // Limpeza do UpgradeRoom
}