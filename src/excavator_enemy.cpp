#include "excavator_enemy.h"
#include "game_room.h"
#include "globals.h"

sf::Texture ExcavatorEnemy::_texture;

const float height = 100; // Tamanho visual

ExcavatorEnemy::ExcavatorEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room)
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room) {

    _current_damage = damage;      // Comeca com o dano base do construtor
    _max_damage = damage * 100.0;  // O dano maximo eh 100x o inicial (sujeito a mudancas)
    _ramp_up_rate = 2.0;           // Aumenta 2 de dano a cada hit

    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setSize({width, height});
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    _shape.setPosition(get_position());
}

bool ExcavatorEnemy::can_walk(double next_position) {
    // Pra quando encostar no muro
    return next_position > WALL_POSITION_X + WALL_WIDTH;
}

void ExcavatorEnemy::run(double dt) {
    Enemy::run(dt);
}

void ExcavatorEnemy::draw() {
    _shape.setTexture(&_texture);
    Enemy::draw();
}

void ExcavatorEnemy::attack() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);
    
    // Aplica o dano atual no muro
    game_room.get_wall().hit(*this, _current_damage);

    // Aumenta o muro pro proximo hit
    _current_damage += _ramp_up_rate;

    // Trava no limite maximo
    if (_current_damage > _max_damage) {
        _current_damage = _max_damage;
    }
}

bool ExcavatorEnemy::load_texture(const std::string& file_path) {
    return _texture.loadFromFile(file_path);
}