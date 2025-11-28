#include "monkey_projectile.h"
#include <cmath>

sf::Texture MonkeyProjectile::_texture;

MonkeyProjectile::MonkeyProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, double slowdown_pct, Room &room)
    : TroopProjectile(position, target, damage, speed, room, ProjectileType::MonkeyProjectileType), _shape({35, 35}) {
    _slowdown_pct = slowdown_pct;

    _shape.setTexture(&_texture);
    _shape.setOrigin(_shape.getGlobalBounds().getSize() * .5f);
}

void MonkeyProjectile::draw() {
    _shape.setPosition(_position);

    _room.get_window().draw(_shape);
}

void MonkeyProjectile::run(double dt) {
    TroopProjectile::run(dt);

    if (_target.lock()) { // faz o projetil andar em parabola (MT FODA)
        const double acc = 10;
        _v_speed += acc * dt;
        _position.y += _v_speed * dt;
    }

    const double angular_speed = 90;
    _shape.setRotation(angular_speed * dt + _shape.getRotation());
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