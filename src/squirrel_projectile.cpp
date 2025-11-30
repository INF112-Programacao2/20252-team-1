#include "squirrel_projectile.h"
#include "game_room.h"
#include "wave_manager.h"
#include "game_manager.h"
#include "visual_effect.h"
#include <iostream>

sf::Texture SquirrelProjectile::_texture;

SquirrelProjectile::SquirrelProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, double radius, Room &room)
    : TroopProjectile(position, target, damage, speed, room, ProjectileType::SquirrelProjectileType), _shape({30, 30}) {
    _radius = radius;

    _shape.setTexture(&_texture);
    // centraliza a origem para facilitar rotacao e posicionamento
    _shape.setOrigin(_shape.getGlobalBounds().getSize() * .5f);
}

void SquirrelProjectile::draw() {
    _shape.setPosition(_position);
    _room.get_window().draw(_shape);
}

void SquirrelProjectile::run(double dt) {
    TroopProjectile::run(dt);

    if (_target.lock()) { // faz o projetil andar em parabola (MT FODA)
        const double acc = 10;
        _v_speed += acc * dt;
        _position.y += _v_speed * dt;
    }
    // gira a noz enquanto voa (gira mais rapido que a banana)
    _shape.rotate(360.0 * dt);
}

void SquirrelProjectile::on_hit(std::shared_ptr<Enemy> direct_hit) {
    // chamar TroopProjectile::on_hit(enemy) da merda -> ataca duas vezes
    // pois o alvo principal tambem estara dentro do circulo da explosao

    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    // vermelho translucido
    // 50 opacidade
    game_room.add_effect(std::make_unique<VisualEffect>(
        _position, _radius, 0.5, sf::Color(255, 50, 50, 150), _room
    ));

    // pega todos os inimigos no raio de explosao
    std::vector<std::shared_ptr<Enemy>> targets = game_room.get_wave_manager().get_enemys_on_circle(_position, _radius);

    // calcula o dano final
    int final_damage = _damage * GameManager::get_instance().get_troop_damage_multiplier();

    for (auto &enemy : targets) {
        apply_damage(enemy, enemy->get_type_multiplier(_type));
    }

    destroy();
}

double SquirrelProjectile::get_radius() {
    return _radius;
}

void SquirrelProjectile::set_radius(double radius) {
    _radius = radius;
}

bool SquirrelProjectile::load_texture(std::string file_path) {
    return SquirrelProjectile::_texture.loadFromFile(file_path);
}