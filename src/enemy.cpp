#include "enemy.h"
#include "room.h"
#include "game_manager.h"
#include "globals.h"
#include <iostream>

Enemy::Enemy(int base_life, int damage, int line, double base_cooldown, double points, Room &room)
    : _damage(damage), _line(line), _base_cooldown(base_cooldown), _points(points), _room(room),
      _shape(sf::Vector2f(50.0, 50.0)) { // _shape ta com um tamanho de teste
    //_health.set_life(base_life);
    _position = GAME_SIZE_X;
    _cooldown = 0;
    _shape.setFillColor(sf::Color::Red);
    float y_pos = HUD_HEIGHT + PADDING_Y + (_line * GAP_Y);
    _shape.setPosition(_position, y_pos);
    }

Enemy::~Enemy() = default;

int Enemy::get_line() {
    return _line;
}

bool Enemy::can_walk(double next_position) {
    if(next_position <= (WALL_POSITION_X + WALL_WIDTH)) {
        return false;
    }
    return true; 
}

void Enemy::attack() {}

void Enemy::run(double dt) {
    //if(_health.is_dead()) {
    //    return; 
    //}

    if(_cooldown > 0) {
        _cooldown -= dt;
    }

    double speed = 50; // 50 pixels por segundo(teste)
    double next_position_x = _position - (speed * dt); // Calcula a proxima posicao

    if(can_walk(next_position_x)) {
        // Caso ele possa andar para a proxima posicao
        _position = next_position_x; // Atualiza a posicao atual
        _shape.setPosition(_position, _shape.getPosition().y); // Atualiza o x
    } 
    else {
        // Caso nao possa mais andar (chegou no muro)
        if (_cooldown <= 0) {  // E tenha acabado o cooldown de ataque
            attack();  // o inimigo ataca
            _cooldown = _base_cooldown; // e o timer reseta
        }
    }
}

void Enemy::damage(int life) {
    //_health.decrease_life(life);
}

void Enemy::draw() {
    _room.get_window().draw(_shape); // Teste
}

bool Enemy::collide(sf::Vector2f position) {
    return _shape.getGlobalBounds().contains(position);
}

void Enemy::destroy() {} // Esperando WaveManager