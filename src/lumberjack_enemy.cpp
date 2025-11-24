#include "lumberjack_enemy.h"
#include "game_room.h"

sf::Texture LumberjackEnemy::_texture;

const float height = 100;

LumberjackEnemy::LumberjackEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room) 
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room) {

    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    _shape.setSize({width, height});
}

bool LumberjackEnemy::can_walk(double next_position) {
    return next_position > WALL_POSITION_X + WALL_WIDTH;
}

void LumberjackEnemy::run(double dt) {
    Enemy::run(dt);
}

void LumberjackEnemy::draw() {
    _shape.setTexture(&_texture);
    Enemy::draw();
}

void LumberjackEnemy::attack() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);
    game_room.get_wall().hit(*this, _damage);
}

bool LumberjackEnemy::load_texture(const std::string& file_path) {
    return _texture.loadFromFile(file_path);
}