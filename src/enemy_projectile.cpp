#include "enemy_projectile.h"
#include <SFML/Graphics.hpp>

EnemyProjectile::EnemyProjectile(sf::Vector2f position, std::weak_ptr<Enemy> parent, Wall &target, 
                                 int damage, double speed, Room &room)
    : Projectile(position, sf::Vector2f(-1.0f, 0.0f), damage, speed, room),
      _parent(parent), _target(target) {}

void EnemyProjectile::run(double dt) {
    // funcao que move o projetil ao muro e checa colisao

    // checar se colidiu com o muro
    if (_target.collide(_position)) {
        // aplicar dano e efeito no muro
        _target.hit(*this);

        destroy();
        return;
    }

    // andar
    _position += (float)(_speed * dt) * _direction;
}

std::shared_ptr<Enemy> EnemyProjectile::get_parent() {
    return _parent.lock();
}