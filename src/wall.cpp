#include "wall.h"
#include "room_manager.h"
#include "game_manager.h"
#include "globals.h"
#include "enemy_projectile.h"
#include "enemy.h"
#include <iostream> //! DEBUG

Wall::Wall(int base_life, int spike_damage, Room &room)
    : _health(base_life, std::bind(&Wall::destroy, this)), _spike_damage(spike_damage), _room(room),
      _flash_timer(.15), _shape({WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT}),
      _damage_text(sf::Vector2f(WALL_POSITION_X + WALL_WIDTH, DESKTOP_SIZE.y * .5), 1.0, room) {

    _collider = sf::Rect<float>(
        sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT),
        sf::Vector2f(WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT));

    _shape.setFillColor(sf::Color(128, 128, 128)); // cor cinza para o muro
};

Wall::~Wall() = default;

void Wall::destroy() {
    std::cout << "O muro foi de arrasta pra cima" << std::endl;
}

bool Wall::collide(sf::Vector2f position) {
    return _collider.contains(position) || position.x < _collider.left;
}

void Wall::start_burning(double duration, int damage) {
    _burning_time += duration;
    _burn_dps = static_cast<double>(damage); // define dps baseado no dano do inimigo fogo
}

void Wall::extinguish(double duration) {
    if (_burning_time > 0) {
        _burning_time -= duration;
        if (_burning_time < 0)
            _burning_time = 0;
    }
}

void Wall::run(double dt) {
    _burning_timer.update(dt);
    _flash_timer.update(dt);
    _damage_text.run(dt);

    // logica do dano de fogo (damage over time)
    if (_burning_time > 0) {
        _burning_time -= dt;

        // acumula o dano (pq health � int, nao da pra tirar 0.3 de vida)
        _burn_damage_accumulator += _burn_dps * dt;

        if (_burn_damage_accumulator >= 1.0) {
            int damage_to_apply = (int)_burn_damage_accumulator;
            _health.decrease_life(damage_to_apply);
            _burn_damage_accumulator -= damage_to_apply;
        }
    }
}

void Wall::draw() {
    _shape.setPosition(sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT));

    // cor base
    sf::Color color = sf::Color(128, 128, 128);

    // se estiver pegando fogo, fica laranja
    if (_burning_time > 0) {
        // oscila um pouco o vermelho pra parecer fogo
        int red_oscillation = 200 + (std::rand() % 55);
        color = sf::Color(red_oscillation, 100, 0);
    }

    // se tomou hit recentemente, pisca branco (prioridade sobre o fogo)
    if (!_flash_timer.timeout())
        color = sf::Color::White;

    _shape.setFillColor(color);
    _room.get_window().draw(_shape);

    _damage_text.draw();
}

void Wall::hit(EnemyProjectile &projectile) {
    // texto mostrando o dano
    sf::Text text(std::to_string(projectile.get_damage()), GameManager::get_instance().get_font(), 20);
    text.setFillColor(sf::Color::Red);
    _damage_text.set_text(text);
    _damage_text.set_position(projectile.get_position());
    _damage_text.restart();

    _health.decrease_life(projectile.get_damage());
    _flash_timer.restart();

    auto enemy = projectile.get_parent();
    if (enemy) {
        enemy->damage(_spike_damage);
    }
}

void Wall::hit(Enemy &enemy, int damage) {
    // texto mostrando o dano
    sf::Text text(std::to_string(damage), GameManager::get_instance().get_font(), 20);
    text.setFillColor(sf::Color::Red);
    _damage_text.set_text(text);
    _damage_text.set_position(enemy.get_position() - sf::Vector2f(75, 0));
    _damage_text.restart();

    _health.decrease_life(damage);
    _flash_timer.restart();

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

    if (max_life <= 0)
        max_life = 1;

    // calcula a porcentagem de vida
    float ratio = static_cast<float>(current_life) / static_cast<float>(max_life);

    // desenha a barra de vida
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(x_pos, y_pos);
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(2.0f);
    background.setOutlineColor(sf::Color::White);

    sf::RectangleShape foreground(sf::Vector2f(width * ratio, height));
    foreground.setPosition(x_pos, y_pos);

    if (ratio < 0.3f)
        foreground.setFillColor(sf::Color::Red);
    else
        foreground.setFillColor(sf::Color::Green);

    sf::Font &font = GameManager::get_instance().get_font();

    // texto da barra de vida
    sf::Text label_text;
    label_text.setFont(font);
    label_text.setString("Muro:");
    label_text.setCharacterSize(24);
    label_text.setFillColor(sf::Color::White);
    sf::FloatRect label_bounds = label_text.getLocalBounds();
    label_text.setOrigin(0, label_bounds.top + label_bounds.height / 2.0f);
    label_text.setPosition(x_pos - label_bounds.width - 15.0f, y_pos + height / 2.0f);

    // texto do valor da vida
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
                         text_bounds.top + text_bounds.height / 2.0f);
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