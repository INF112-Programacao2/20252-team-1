#include "elephant_projectile.h"
#include "game_room.h"
#include "globals.h"
#include <cmath>

sf::Texture ElephantProjectile::_texture;

//normalize de troop_projectile.cpp posto aqui pra evitar include circular
sf::Vector2f normalize_dir(sf::Vector2f vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length == 0.0f) return sf::Vector2f(1.0f, 0.0f);
    return vec / length;
}

ElephantProjectile::ElephantProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, double fire_reduce, Room& room)
    : TroopProjectile(position, target, damage, speed, room), _fire_reduce(fire_reduce) {

    _shape.setSize(sf::Vector2f(30.0f, 30.0f)); //ajuste
    _shape.setOrigin(_shape.getSize() / 2.0f);
    _shape.setTexture(&_texture);

    //calcula direcao fixa imediatamente
    std::shared_ptr<Enemy> enemy = _target.lock();
    if (enemy) {
        _direction = normalize_dir(enemy->get_position() - _position);
    }
    else {
        _direction = sf::Vector2f(1.0f, 0.0f); //default pra dreita se o alvo morreu instantaneamente
    }
}

void ElephantProjectile::draw() {
    _shape.setPosition(_position);
    _room.get_window().draw(_shape);
}

void ElephantProjectile::run(double dt) {
    //vai direto, projetil impreciso -> Bug ou feature?
    _position += (float)(_speed * dt) * _direction;

    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    //logica de extincao de fogo no muro
    if (!_has_extinguished && _position.x > WALL_POSITION_X) {
        game_room.get_wall().extinguish(_fire_reduce);
        _has_extinguished = true;
    }

    //logica de colisao padrao
    if (auto hit = game_room.get_wave_manager().get_enemy_colliding(_position)) {
        on_hit(hit);
        destroy();
        return;
    }

    //saiu da tela
    if (!GAME_RECT.contains(_position)) {
        destroy();
    }
}

double ElephantProjectile::get_fire_reduce() {
    return _fire_reduce;
}

void ElephantProjectile::set_fire_reduce(double fire_reduce) {
    _fire_reduce = fire_reduce;
}

void ElephantProjectile::on_hit(std::shared_ptr<Enemy> enemy) {
    TroopProjectile::on_hit(enemy); //aplica dano
}

bool ElephantProjectile::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}