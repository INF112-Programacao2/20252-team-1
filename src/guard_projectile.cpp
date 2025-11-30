#include "guard_projectile.h"

sf::Texture GuardProjectile::_texture;

GuardProjectile::GuardProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, Clock stun_duration, Room& room)
    : TroopProjectile(position, target, damage, speed, room, ProjectileType::GuardProjectileType), _stun_duation(stun_duration), _shape({ 35, 35 }) {
    _shape.setTexture(&_texture);
    _shape.setOrigin(_shape.getGlobalBounds().getSize() * .5f);
}

void GuardProjectile::draw() {
    _shape.setPosition(_position);
    _room.get_window().draw(_shape);
}

void GuardProjectile::run(double dt) {
    TroopProjectile::run(dt);
}

//logica de stun
void GuardProjectile::on_hit(std::shared_ptr<Enemy> enemy) {
    if (enemy) {
        //aplica 0 de velocidade on_hit
        enemy->apply_slowdown(0.0, _stun_duation.get_timeout_duration());
    }

    //chama o metodo base para aplicar dano e destruir o projetil
    TroopProjectile::on_hit(enemy);
}

Clock GuardProjectile::get_stun_duration() {
    return _stun_duation;
}

void GuardProjectile::set_stun_duration(Clock stun_duration) {
    _stun_duation = stun_duration;
}

bool GuardProjectile::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}