#include "upgradeUI.h"
#include "game_manager.h"
#include <sstream>
#include <utility>

const float width = 250.f;
const float height = 300.f;
const float padding_x = 20.f;
const int desc_tamanho = 14;

UpgradeUI::UpgradeUI(std::string nome, int preco, int incremento, int level, int max_level, std::string descricao,
    sf::Vector2f position, Room &room, std::function<void()> on_buy_callback)
    : _preco(preco),
      _base_price(preco),
      _incremento(incremento),
      _level(level),
      _max_level(max_level),
      _position(position),
      _room(room),
      _on_buy_callback(std::move(on_buy_callback)),
      _feedback_text(sf::Vector2f(0, 0), 1.5, room) {
    _nome.setString(nome);
    _colider = sf::Rect<float>(position.x, position.y, width, height);
    _font = GameManager::get_instance().get_font();

    // criacao da quebra de linha na descricao
    const float largura_max = width - 2 * padding_x;
    _descricao.setFont(_font);
    _descricao.setCharacterSize(desc_tamanho);

    std::stringstream ss(descricao);
    std::string palavra;
    std::string quebra_linha;
    std::string linha_atual;

    while (ss >> palavra) {
        std::string test_line = linha_atual.empty() ? palavra : linha_atual + " " + palavra;

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

    // Circulos dos niveis
    _level_circle.setRadius(6.f);
    _level_circle.setOutlineThickness(1.f);
    _level_circle.setOutlineColor(sf::Color::White);

    // Texto do nivel
    _level_label.setFont(_font);
    _level_label.setString("Nivel:");
    _level_label.setCharacterSize(18);

    // Texto do preco
    _preco_text.setFont(_font);
    _preco_text.setCharacterSize(18);
}

UpgradeUI::~UpgradeUI() = default;

bool UpgradeUI::buy(const std::vector<sf::Event> &event_queue) {
    for(const sf::Event &event : event_queue) {
        if(event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left) {

            // Verifica se a posicao do mouse colide com a posicao do colider
            if(_colider.contains((sf::Vector2f)_room.get_mouse_position())) {
                GameManager& gm = GameManager::get_instance();
                sf::Text msg_text;
                msg_text.setFont(_font);
                msg_text.setCharacterSize(15);

                if(_level < _max_level) {
                    if(gm.remove_points(_preco)) { // Verifica se tem pontos o bastante
                        _level++;
                        _preco += _incremento; // Aumenta o preço para a proxima compra
                        // Executa o upgrade
                        if(_on_buy_callback) {
                            _on_buy_callback();
                        }

                        // Texto que aparece quando o jogador compra um upgrade
                        msg_text.setString("Subiu de nivel!");
                        msg_text.setFillColor(sf::Color::Green);
                        sf::FloatRect bounds = msg_text.getLocalBounds();
                        msg_text.setOrigin(bounds.width / 2, bounds.height / 2);
                        _feedback_text.set_text(msg_text);
                        _feedback_text.set_position(_position + sf::Vector2f(width / 2, height / 2));
                        _feedback_text.restart();

                        return true;
                    } else {
                        // Texto que aparece caso o jogador nao tenha pontos suficientes para comprar
                        msg_text.setString("Pontos insuficientes!");
                        msg_text.setFillColor(sf::Color::Red);
                        sf::FloatRect bounds = msg_text.getLocalBounds();
                        msg_text.setOrigin(bounds.width / 2, bounds.height / 2);
                        _feedback_text.set_text(msg_text);
                        _feedback_text.set_position(_position + sf::Vector2f(width / 2, height / 2));
                        _feedback_text.restart();
                    }
                }
            }
        }
    }

    return false;
}

void UpgradeUI::run(double dt, const std::vector<sf::Event> &event_queue) {
    buy(event_queue);
    _feedback_text.run(dt);
}

void UpgradeUI::draw() {
    // Verifica se o mouse esta passando por cima
    bool is_hovering = _colider.contains((sf::Vector2f)_room.get_mouse_position());

    // Define a nova escala caso o mouse esteja por cima do botao
    float scale = is_hovering ? 1.1f : 1.0f;

    sf::RectangleShape rectangle({width, height});

    if(is_hovering) {
        rectangle.setFillColor(sf::Color(125, 65, 40));
        rectangle.setOutlineColor(sf::Color::Yellow);
    } else {
        rectangle.setFillColor(sf::Color(85, 25, 0));
        rectangle.setOutlineColor(sf::Color::White);
    }

    rectangle.setOrigin(width / 2.f, height / 2.f);
    rectangle.setPosition(_position.x + (width / 2.f), _position.y + (height / 2.f));

    // Aplica a escala
    rectangle.setScale(scale, scale);
    rectangle.setOutlineThickness(5.f);

    // Tratando de desenhar o _nome
    _nome.setFont(_font);
    _nome.setCharacterSize(24);
    _nome.setPosition(_position + sf::Vector2f(padding_x, 30.f));
    _descricao.setPosition(_position + sf::Vector2f(padding_x, 60.f));

    // Posiciona o texto "Nivel:"
    float rodape_y_1 = height - 55.f;
    _level_label.setPosition(_position + sf::Vector2f(padding_x, rodape_y_1));

    // Tratando de desenhar o _preco
    if(_level >= _max_level) {
        _preco_text.setString("MAXIMO");
        _preco_text.setFillColor(sf::Color::Red);
    }
    else {
        _preco_text.setString("Preco: " + std::to_string(_preco));
        _preco_text.setFillColor(sf::Color::Yellow);
    }

    float rodape_y_2 = height - 25.f;
    _preco_text.setPosition(_position + sf::Vector2f(padding_x, rodape_y_2));

    // Desenha os textos na janela
    _room.get_window().draw(rectangle);
    _room.get_window().draw(_nome);
    _room.get_window().draw(_descricao);
    _room.get_window().draw(_preco_text);
    _room.get_window().draw(_level_label);

    // Posicao dos circulos de nivel
    float raio = 6.f;
    float espacamento = 5.f; // Espaco entre os circulos

    float start_x = _level_label.getGlobalBounds().left + _level_label.getGlobalBounds().width + 10;
    float start_y = _position.y + rodape_y_1 - 8.f;

    for(int i = 0; i < _max_level; i++) {
        // Calcula a posicao do circulo em especifico
        float x = start_x + i * (raio * 2 + espacamento);
        _level_circle.setPosition(x, start_y);

        // Decide a cor
        _level_circle.setFillColor((i < _level) ? sf::Color::White : sf::Color::Transparent);

        _room.get_window().draw(_level_circle);
    }

    _feedback_text.draw();
}

void UpgradeUI::reset_feedback() {
    _feedback_text.hide();
}

int UpgradeUI::get_level() const {
    return _level;
}

void UpgradeUI::set_level(int level) {
    _level = level;
    _preco = _base_price + (_incremento * level);
    for (int i = 0; i < level; i++)
        _on_buy_callback(); // compra os upgrades
}