#include "upgrade_room.h"

UpgradeRoom::UpgradeRoom(sf::RenderWindow &window, RoomManager &room_manager)
    : Room(window, room_manager),
      _upgrade_ui_1("Upgrade 1", 100, 1, "Descricao do upgrade gigante do upgrade room so pra testar se ta funcionando a quebra de linha, nao to afim de fazer isso nao Nobre 1",
                    sf::Vector2f(50, 50), *this)
{
  //_upgrade_ui_1 = new UpgradeUI("Upgrade 1", 100, 1, "Descricao do upgrade 1",
  //sf::Vector2f(50, 50), *this);
}

UpgradeRoom::~UpgradeRoom() = default;

void UpgradeRoom::start() {
  // Inicialização do UpgradeRoom
}

void UpgradeRoom::run(double dt, const std::vector<sf::Event> &event_queue) {
  // Lógica principal do UpgradeRoom

  _window.clear(sf::Color::Black);
  // Desenhar elementos do UpgradeRoom aqui

  _upgrade_ui_1.draw();

  // _upgrade_ui_1->run(dt, event_queue);

  _window.display();
}

void UpgradeRoom::end() {
  // Limpeza do UpgradeRoom
}