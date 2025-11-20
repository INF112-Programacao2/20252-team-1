#include "enemy.h"
#include "game_room.h"
#include "game_manager.h"
#include "globals.h"
#include <iostream>

const float width = 100.0;

Enemy::Enemy(int base_life, int damage, int line, double base_cooldown, double points, Room &room)
    : _damage(damage), _line(line), _base_cooldown(base_cooldown), _points(points), _room(room),
      _shape(sf::Vector2f(width, 100.0)), _health(100, [this]() { this->destroy(); }) { // _shape ta com um tamanho de teste

    _health.set_life(base_life);
    _position_x = GAME_SIZE_X;
    _cooldown = 0;
    _shape.setFillColor(sf::Color::Red);

    // numeros magicos por enquanto
    _shape.setPosition(get_position() - sf::Vector2f(width / 2, 50));
}

Enemy::~Enemy() = default;

int Enemy::get_line() {
    return _line;
}

sf::Vector2f Enemy::get_position() {
    return sf::Vector2f(_position_x + width / 2, GameManager::get_line_pos(_line));
}

bool Enemy::can_walk(double next_position) {
    return next_position > WALL_POSITION_X + WALL_WIDTH;
}

void Enemy::attack() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);
    game_room.get_wave_manager().spawn_projectile(std::make_unique<EnemyProjectile>(
        get_position(), shared_from_this(), game_room.get_wall(), 10, 100.0, _room));
}

void Enemy::run(double dt) {
    if(_health.is_dead()) {
        return;
    }

    if (_cooldown > 0) {
        _cooldown -= dt;
    }

    //! DEBUG
    if (_cooldown <= 0) {           // E tenha acabado o cooldown de ataque
        attack();                   // o inimigo ataca
        _cooldown = _base_cooldown; // e o timer reseta
    }

    double speed = 50;                                   // 50 pixels por segundo(teste)
    double next_position_x = _position_x - (speed * dt); // Calcula a proxima posicao

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
    _health.decrease_life(life * GameManager::get_instance().get_damage_multiplier());
}

void Enemy::draw() {
    _shape.setPosition(get_position() - sf::Vector2f(.5, .5) * width);
    _room.get_window().draw(_shape);
}

bool Enemy::collide(sf::Vector2f position) {
    _shape.setPosition(get_position() - sf::Vector2f(.5, .5) * width);
    return _shape.getGlobalBounds().contains(position);
}

void Enemy::destroy() {}