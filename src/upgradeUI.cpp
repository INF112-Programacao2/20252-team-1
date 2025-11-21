#include "upgradeUI.h"
#include "game_manager.h"
#include <sstream>

const float width = 150.f;
const float height = 300.f;
const int desc_tamanho = 14;
UpgradeUI::UpgradeUI(std::string nome, int preco, int level,
                     std::string descricao, sf::Vector2f position, Room &room)
    : _preco(preco), _level(level), _position(position), _room(room) {
  _nome.setString(nome);
  _colider = sf::Rect<float>(position.x, position.y, width,
                             height); // Exemplo de tamanho
  _font = GameManager::get_instance().get_font();

  // criacao da quebra de linha na descricao
  const float largura_max = 240.f; // 250 (largura total) - 10 (padding)
  _descricao.setFont(_font);
  _descricao.setCharacterSize(desc_tamanho);

  std::stringstream ss(descricao);
  std::string palavra;
  std::string quebra_linha;
  std::string linha_atual;

  while (ss >> palavra) {
    std::string test_line =
        linha_atual.empty() ? palavra : linha_atual + " " + palavra;

    sf::Text temp_text(test_line, _font, desc_tamanho);
    float bounds_width = temp_text.getLocalBounds().width;

    if (bounds_width > largura_max) {
      if (!linha_atual.empty()) {
        quebra_linha += linha_atual + "\n";
        linha_atual = palavra;
      }
    } else {
      linha_atual = test_line;
    }
  }

  quebra_linha += linha_atual;
  _descricao.setString(quebra_linha);
}

UpgradeUI::~UpgradeUI() = default;

bool UpgradeUI::buy(const std::vector<sf::Event> &event_queue) {
  for (const sf::Event &event : event_queue) {
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left &&
        _colider.contains((sf::Vector2f)_room.get_mouse_position())) {
      _level++;
      return true;
    }
  }
  return false;
}

void UpgradeUI::run(double dt, const std::vector<sf::Event> &event_queue) {
  buy(event_queue);
}

void UpgradeUI::draw() {
  sf::RectangleShape rectangle({250.f, 250.f});

  // 3. Personalizar o retângulo
  rectangle.setFillColor(sf::Color::Black); // Cor de preenchimento preta
  rectangle.setPosition(
      _position +
      sf::Vector2f(width - 150, height - 300)); // Posição na tela (x, y)
  rectangle.setOutlineColor(sf::Color::White);  // Cor do contorno branca
  rectangle.setOutlineThickness(5.f); // Espessura do contorno de 2 pixels

  // tratando de desenhar o _nome
  _nome.setFont(_font);
  _nome.setCharacterSize(24);
  _nome.setPosition(
      _position +
      sf::Vector2f(width - 100, height - 275)); // Exemplo de posição

  _descricao.setPosition(
      _position +
      sf::Vector2f(width - 145, height - 240)); // Exemplo de posição

  // tratando de desenhar o _preco
  std::string preco_text = "Preco: " + std::to_string(_preco);
  sf::Text preco_sftext(preco_text, _font, 18);
  preco_sftext.setPosition(
      _position + sf::Vector2f(width - 145, height - 60)); // Exemplo de posição

  // tratando de desenhar o _level
  std::string level_text = "Level: " + std::to_string(_level);
  sf::Text level_sftext(level_text, _font, 18);
  level_sftext.setPosition(
      _position + sf::Vector2f(width + 10, height - 60)); // Exemplo de posição
  _room.get_window().draw(level_sftext);

  // Desenha os textos na janela
  _room.get_window().draw(rectangle);
  _room.get_window().draw(_nome);
  _room.get_window().draw(_descricao);
  _room.get_window().draw(preco_sftext);
  _room.get_window().draw(level_sftext);
}