#include "troop_projectile.h"
#include "projectile.h"
#include <cmath>
#include <SFML/Graphics.hpp>

// Função auxiliar para normalizar um vetor
sf::Vector2f normalize(sf::Vector2f vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length == 0.0f) {
        return sf::Vector2f(0.0f, 0.0f);
    }
    return vec / length;
}

TroopProjectile::TroopProjectile(sf::Vector2f position, Troop &parent, std::weak_ptr<Enemy> target, double speed, Room &room)
    : Projectile(position, sf::Vector2f(1, 0), speed, room), _target(target), _parent(parent) {}

void TroopProjectile::run(double dt) {
    // funcao que move o projetil ao inimigo e checa colisao

    std::shared_ptr<Enemy> enemy = _target.lock();

    if (enemy)
        _direction = normalize(enemy->get_position() - _position);

    _position += (float)(_speed * dt) * _direction;

    // acerta o alvo ou chega ao fim da tela
    if (enemy->collide(_position)) {
        enemy->damage(_damage);
        destroy();

        return;
    }

    // saiu da tela
    if (!GAME_RECT.contains(_position))
        destroy();
}
