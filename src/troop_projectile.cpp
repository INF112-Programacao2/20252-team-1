#include "troop_projectile.h"
#include "projectile.h"
#include <cmath>
#include <SFML/Graphics.hpp>

// Função auxiliar para normalizar um vetor
sf::Vector2f normalize(sf::Vector2f vec)
{
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length == 0.0f)
    {
        return sf::Vector2f(0.0f, 0.0f);
    }
    return vec / length;
}

TroopProjectile::TroopProjectile(sf::Vector2f position, Troop &parent, Enemy *target, double speed, Room &room)
    : Projectile(
          position,
          // normaliza pra direcionar ao inimigo
          (target != nullptr) ? normalize(target->get_position() - position) : sf::Vector2f(0.0f, -1.0f),
          speed,
          room),

      _target(target),
      _valid_target(target != nullptr),
      _parent(parent)
{
}

//funcao que move o projetil ao inimigo e checa colisao
void TroopProjectile::run(float dt)
{

    if (!_valid_target || _target == nullptr)
    {
        _valid_target = false;
        destroy();
    }
    else
    {
        _direction = normalize(_target->get_position() - _position);
    }

    _position += (float)_speed * dt * _direction;

    if (_target->collide(_position))
    {
        //_target->take_damage(_damage);
        destroy();
        return;
    }
}
