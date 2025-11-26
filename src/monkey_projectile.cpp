#include "monkey_projectile.h"
#include <cmath>


sf::Texture MonkeyProjectile::_texture;

MonkeyProjectile::MonkeyProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, double slowdown_pct, Room& room)
    : TroopProjectile(position, target, damage, speed, room) {
    _slowdown_pct = slowdown_pct;
    _type = ProjectileType::MonkeyProjectileType;

    _sprite.setTexture(_texture);

    sf::Vector2u texture_size = _texture.getSize();
    _sprite.setOrigin(texture_size.x / 2.0f, texture_size.y / 2.0f);

    float target_size = 35.0f; //logica de escalamento, a banana eh enorme

    float scale_factor = target_size /std::max(texture_size.x, texture_size.y);

    _sprite.setScale(scale_factor, scale_factor);
}

void MonkeyProjectile::draw() {
    _sprite.setPosition(_position);

    if (_direction.x != 0 || _direction.y != 0) {
        float angle = std::atan2(_direction.y, _direction.x) * 180 / 3.14159;
        _sprite.setRotation(angle);
    }

    _room.get_window().draw(_sprite);
}

void MonkeyProjectile::run(double dt){
    TroopProjectile::run(dt);
}

double MonkeyProjectile::get_slowdown_pct() {
    return _slowdown_pct;
}

void MonkeyProjectile::on_hit(std::shared_ptr<Enemy> enemy) {
    TroopProjectile::on_hit(enemy);

    if (enemy) {
        enemy->apply_slowdown(1.0 - _slowdown_pct, 2.0);
    }

}

bool MonkeyProjectile::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}