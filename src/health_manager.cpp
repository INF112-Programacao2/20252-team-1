#include "health_manager.h"

HealthManager::HealthManager(int max_life, std::function<void()> on_death_callback)
    : _max_life(max_life), _life(max_life), _on_death_callback(std::move(on_death_callback)) {
}
HealthManager::~HealthManager() = default;

void HealthManager::set_life(int new_life) {
    _life = std::max(0, std::min(_max_life, new_life));
    if (_life <= 0 && _on_death_callback)
        _on_death_callback();
}

void HealthManager::set_max_life(int max_life) {
    _max_life = max_life;
    if (_life > _max_life)
        _life = _max_life;
}

void HealthManager::decrease_life(int amount) {
    set_life(_life - amount);
}

void HealthManager::increase_max_life(int amount) {
    set_max_life(_max_life + amount);
}

void HealthManager::increase_life(int amount) {
    set_life(_life + amount);
}

void HealthManager::set_on_death_callback(std::function<void()> on_death_callback) {
    _on_death_callback = std::move(on_death_callback);
}

bool HealthManager::is_dead() {
    return _life <= 0;
}

int HealthManager::get_life() const {
    return _life;
}

void HealthManager::draw_health_bar(sf::RenderWindow &window, sf::Vector2f position) {
    if (_life >= _max_life)
        return;

    const float bar_width = 100.0f; // isso aqui eh pra teste, depois muda
    const float bar_height = 10.0f;

    sf::RectangleShape background(sf::Vector2f(bar_width, bar_height));
    background.setFillColor(sf::Color(100, 100, 100)); // cor cinza pra vida vazia
    background.setPosition(position);

    float life_ratio = static_cast<float>(_life) / static_cast<float>(_max_life);

    sf::RectangleShape foreground(sf::Vector2f(bar_width * life_ratio, bar_height));
    foreground.setFillColor(sf::Color(0, 255, 0)); // cor verde pra vida cheia
    foreground.setPosition(position);

    // Desenha as barras
    window.draw(background);
    window.draw(foreground);
}
