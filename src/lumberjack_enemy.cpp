#include "lumberjack_enemy.h"
#include "game_room.h"

sf::Texture LumberjackEnemy::_texture;

const float height = 100;

LumberjackEnemy::LumberjackEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room)
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room) {

    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    _shape.setSize({width, height});
    _shape.setTexture(&_texture);
}

void LumberjackEnemy::run(double dt) {
    Enemy::run(dt);
}

void LumberjackEnemy::attack(FieldTroop* field_troop) {
    // ve se tem alguma fieldtroop na frente
    if (field_troop) {
        field_troop->hit(_damage);
        return;
    }

    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    game_room.get_wall().hit(*this, _damage);
}

bool LumberjackEnemy::load_texture(const std::string &file_path) {
    return _texture.loadFromFile(file_path);
}

double LumberjackEnemy::get_type_multiplier(ProjectileType type) {
    switch (type) {
    case ProjectileType::AnteaterProjectileType:
        return 1.05;
    case ProjectileType::ElephantProjectileType:
        return 0.5;
    case ProjectileType::DolphinProjectileType:
        return 0.75;
    case ProjectileType::GuardProjectileType:
        return 1.5;

    default:
        return 1.0;
    }
}