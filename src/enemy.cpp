#include "enemy.h"
#include "game_room.h"
#include "game_manager.h"
#include "globals.h"
#include <iostream>

const float height = 100.0;

Enemy::Enemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room)
    : _damage(damage), _line(line), _speed(speed), _base_cooldown(base_cooldown), _points(points), _room(room),
      _shape(sf::Vector2f(height, height)), _health(base_life, [this]() { this->destroy(); }), // _shape ta com um tamanho de teste
      _flash_timer(.25) {

    _health.set_life(base_life);
    _position_x = GAME_SIZE_X;
    _cooldown = 0;

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
    return sf::Vector2f(_position_x + height / 2, GameManager::get_line_pos(_line));
}

bool Enemy::can_walk(double next_position) {
    //! DEBUG
    return next_position > WALL_POSITION_X + WALL_WIDTH + 300;
}

void Enemy::attack() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);
    game_room.get_wave_manager().spawn_projectile(std::make_unique<EnemyProjectile>(
        get_position(), shared_from_this(), game_room.get_wall(), 10, 100.0, _room));
}

void Enemy::run(double dt) {
    if (is_destroyed())
        return;

    _flash_timer.update(dt);
    if (_cooldown > 0)
        _cooldown -= dt;

    double next_position_x = _position_x - (_speed * dt); // Calcula a proxima posicao

    if (can_walk(next_position_x)) {
        // Caso ele possa andar para a proxima posicao
        _position_x = next_position_x; // Atualiza a posicao atual
    } else {
        // Caso nao possa mais andar (chegou no muro)
        if (_cooldown <= 0) {           // E tenha acabado o cooldown de ataque
            attack();                   // o inimigo ataca
            _cooldown = _base_cooldown; // e o timer reseta
        }
    }
}

void Enemy::damage(int life) {
    if (life <= 0)
        return;

    _flash_timer.restart();
    _shape.setFillColor(sf::Color::Red);
    _health.decrease_life(life * GameManager::get_instance().get_damage_multiplier());
}

void Enemy::draw() {
    if (_flash_timer.timeout())
        _shape.setFillColor(sf::Color::White);

    _shape.setPosition(get_position());
    _room.get_window().draw(_shape);

    _health.draw_health_bar(_room.get_window(), get_position() + sf::Vector2f(0, 70));
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