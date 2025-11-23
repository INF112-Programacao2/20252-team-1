#include "wall.h"
#include "room_manager.h"
#include "game_manager.h"
#include "globals.h"
#include "enemy_projectile.h"
#include "enemy.h"
#include <iostream> //! DEBUG

Wall::Wall(int base_life, int spike_damage, Room &room)
    : _health(base_life, std::bind(&Wall::destroy, this)), _spike_damage(spike_damage), _room(room),
      _flash_timer(.15), _shape({WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT}) {

    _collider = sf::Rect<float>(
        sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT),
        sf::Vector2f(WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT));

    _shape.setFillColor(sf::Color(128, 128, 128)); // cor cinza para o muro
};

Wall::~Wall() = default;

void Wall::destroy() {
    // Callback chamado quando a vida do muro chega a zero -> ondeathcallback
    // a ideia eh ter algo de verdade aqui -> discutir c/ grupo
    std::cout << "O muro foi de arrasta pra cima" << std::endl;
}

bool Wall::collide(sf::Vector2f position) {
    return _collider.contains(position) || position.x < _collider.left;
}

void Wall::run(double dt) {
    _burning_timer.update(dt);
    _flash_timer.update(dt);
}

void Wall::draw() {
    _shape.setPosition(sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT));
    if (_flash_timer.timeout())
        _shape.setFillColor(sf::Color(128, 128, 128)); // cor cinza para o muro

    _room.get_window().draw(_shape);
}

void Wall::hit(EnemyProjectile& projectile) {
    _health.decrease_life(projectile.get_damage());
    _flash_timer.restart();
    _shape.setFillColor(sf::Color::White);

    auto enemy = projectile.get_parent();
    if (enemy) {
        enemy->damage(_spike_damage);
    }
}

void Wall::hit(Enemy& enemy, int damage) {
    _health.decrease_life(damage);
    _flash_timer.restart();
    _shape.setFillColor(sf::Color::White);

    enemy.damage(_spike_damage);
}

int Wall::get_life() {
    return _health.get_life();
}

void Wall::set_life(int amount) {
    _health.set_life(amount);
}

int Wall::get_max_life() {
    return _health.get_max_life();
}

void Wall::set_max_life(int max_life) {
    _health.set_max_life(max_life);
}

void Wall::draw_wall_health_bar() {
    float width = 450.0f;
    float height = 30.0f;
    float x_pos = (_room.get_window().getSize().x / 2.0f) - (width / 2.0f);
    float y_pos = 40.0f; 

    int current_life = _health.get_life();
    int max_life = _health.get_max_life();
    
    if (max_life <= 0) max_life = 1; 

    // Calcula a porcentagem de vida
    float ratio = static_cast<float>(current_life) / static_cast<float>(max_life);

    // Desenha o fundo da barra de vida
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(x_pos, y_pos);
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(2.0f);
    background.setOutlineColor(sf::Color::White);

    // Desenha a vida atual
    sf::RectangleShape foreground(sf::Vector2f(width * ratio, height));
    foreground.setPosition(x_pos, y_pos);

    if (ratio < 0.3f) 
        foreground.setFillColor(sf::Color::Red); // Vermelho se a vida for menor que 30%
    else 
        foreground.setFillColor(sf::Color::Green); // Verde para outras porcentagens

    sf::Font& font = GameManager::get_instance().get_font();

    // Texto "Muro"
    sf::Text label_text;
    label_text.setFont(font);
    label_text.setString("Muro:");
    label_text.setCharacterSize(24);
    label_text.setFillColor(sf::Color::White);
    sf::FloatRect label_bounds = label_text.getLocalBounds();
    label_text.setOrigin(0, label_bounds.top + label_bounds.height / 2.0f);
    label_text.setPosition(x_pos - label_bounds.width - 15.0f, y_pos + height / 2.0f);

    // Texto dentro da barra de vida, que representa os pontos de vida do muro
    sf::Text value_text;
    value_text.setFont(font);
    std::string life_str = std::to_string(current_life) + " / " + std::to_string(max_life);
    value_text.setString(life_str);    
    value_text.setCharacterSize(20);
    value_text.setFillColor(sf::Color::White); 
    value_text.setOutlineThickness(1.0f);
    value_text.setOutlineColor(sf::Color::Black);

    sf::FloatRect text_bounds = value_text.getLocalBounds();
    value_text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, 
                        text_bounds.top  + text_bounds.height / 2.0f);
    value_text.setPosition(x_pos + width / 2.0f, y_pos + height / 2.0f + 5.0f);

    _room.get_window().draw(background);
    _room.get_window().draw(foreground);
    _room.get_window().draw(label_text);
    _room.get_window().draw(value_text);
}

void Wall::increase_max_life(int amount) {
    _health.increase_max_life(amount);
}

void Wall::increase_life(int amount) {
    _health.increase_life(amount);
}

void Wall::increase_spike_damage(int amount) {
    _spike_damage += amount;
}