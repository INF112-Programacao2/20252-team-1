#include "enemy_projectile.h"
#include <SFML/Graphics.hpp>

EnemyProjectile::EnemyProjectile(sf::Vector2f position, Enemy &parent, Wall &target, double speed, Room &room)
    : Projectile(position, sf::Vector2f(-1.0f, 0.0f), speed, room), _parent(parent), _target(target) {}

void EnemyProjectile::run(double dt) {
    // funcao que move o projetil ao muro e checa colisao

    // checar se colidiu com o muro
    if (_target.collide(_position)) {
        destroy();

        // aplicar dano e efeito no muro
        //_target.set_damage();
        //_target.set_effect(_effect_time);
        //_parent.damage(_target._spike_damage); //nao sei se faz sentido o spike damage pegar os atiradores
        return;
    }

    // andar
    _position += (float)(_speed * dt) * _direction;
}
