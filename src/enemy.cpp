#include "enemy.h"
#include "game_room.h"
#include "game_manager.h"
#include "globals.h"
#include <iostream>

const float height = 100.0;

Enemy::Enemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room)
    : _damage(damage), _line(line), _speed(speed), _base_cooldown(base_cooldown),
      _slowdown_timer(0), _points(points), _room(room),
      _shape(sf::Vector2f(height, height)), _health(base_life, [this]() { this->destroy(); }),
      _damage_text(get_position(), 1.0, room) {

    _health.set_life(base_life);
    _position_x = GAME_SIZE_X;
    _cooldown = base_cooldown * .5;

    _shape.setFillColor(sf::Color::White);
    _shape.setOrigin(sf::Vector2f(.5, .5) * height);
    _shape.setPosition(get_position());
}

Enemy::~Enemy() = default;

bool Enemy::is_destroyed() {
    return _health.is_dead();
}

int Enemy::get_line() {
    return _line;
}

sf::Vector2f Enemy::get_position() {
    return sf::Vector2f((float)(_position_x + height / 2), GameManager::get_line_pos(_line));
}

FieldTroop *Enemy::get_field_troop_colliding(double next_position) {
    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    // convertendo explicitamente para evitar warning
    return game_room.get_troop_manager().get_field_troop_at(
        {(float)next_position, GameManager::get_line_pos(_line)});
}

bool Enemy::can_walk(double next_position) {
    return next_position > WALL_POSITION_X + WALL_WIDTH;
}

void Enemy::attack(FieldTroop *field_troop) {
    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);
    game_room.get_wave_manager().spawn_projectile(std::make_unique<EnemyProjectile>(
        get_position(), shared_from_this(), game_room.get_wall(), 10, 100.0, _room, ProjectileType::EnemyBaseProjectile));
}

void Enemy::run(double dt) {
    if (is_destroyed())
        return;

    _slowdown_timer.update(dt);
    if (_slowdown_timer.timeout()) {
        _speed_multiplier = 1.0; // Reseta speed se acabar o tempo
    }

    _damage_text.run(dt);
    _flash_timer.update(dt);

    double current_speed = _speed * _speed_multiplier;           // Calcula a velocidade atual
    double next_position_x = _position_x - (current_speed * dt); // Calcula a proxima posicao

    FieldTroop *field_troop = get_field_troop_colliding(next_position_x);

    if (can_walk(next_position_x) && !field_troop) {
        // Caso ele possa andar para a proxima posicao
        _position_x = next_position_x; // Atualiza a posicao atual
    } else {
        // Caso nao possa mais andar (chegou no muro / field troop)
        if (_cooldown <= 0) {           // E tenha acabado o cooldown de ataque
            attack(field_troop);        // o inimigo ataca
            _cooldown = _base_cooldown; // e o timer reseta
        } else
            _cooldown -= dt;
    }
}

void Enemy::apply_slowdown(double pct, double duration) {
    _speed_multiplier = pct;
    _slowdown_timer.set_timeout_duration(duration); // olhar nova funcao de set no clock.h
    _slowdown_timer.restart();
}

double Enemy::get_type_multiplier(ProjectileType type) {
    return 1.0; // multiplicador base
}

void Enemy::damage(int life) {
    if (life <= 0)
        return;

    int total_damage = life * GameManager::get_instance().get_damage_multiplier();

    // texto mostrando o dano
    sf::Text text(std::to_string(total_damage), GameManager::get_instance().get_font(), 20);
    text.setFillColor(sf::Color::Red);
    _damage_text.set_text(text);
    _damage_text.set_position(get_position() - sf::Vector2f(50, 50));
    _damage_text.restart();

    _flash_timer.restart();
    _shape.setFillColor(sf::Color::Red);
    _health.decrease_life(total_damage);
}

void Enemy::heal(int amount) {
    // texto mostrando a cura
    sf::Text text(std::to_string(amount), GameManager::get_instance().get_font(), 20);
    text.setFillColor(sf::Color::Green);
    _damage_text.set_text(text);
    _damage_text.set_position(get_position() - sf::Vector2f(50, 50));
    _damage_text.restart();

    _health.increase_life(amount);
}

void Enemy::draw() {
    if (_flash_timer.timeout())
        _shape.setFillColor(sf::Color::White);

    _shape.setPosition(get_position());
    _room.get_window().draw(_shape);

    _health.draw_health_bar(_room.get_window(), get_position() + sf::Vector2f(0, 70));
    _damage_text.draw();
}

bool Enemy::collide(sf::Vector2f position) {
    _shape.setPosition(get_position());
    _collider = _shape.getGlobalBounds();

    return _collider.contains(position);
}

void Enemy::destroy() {
    // soma os pontos quando for destruido
    GameManager::get_instance().add_points(_points);
}