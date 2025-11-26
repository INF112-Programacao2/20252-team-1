#include "troop_projectile.h"
#include "projectile.h"
#include "game_room.h"
#include "game_manager.h"
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

TroopProjectile::TroopProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage,
                                 double speed, Room &room)
    : Projectile(position, sf::Vector2f(1, 0), damage, speed, room), _target(target) {

    _shape.setFillColor(sf::Color::Yellow);
}

void TroopProjectile::run(double dt) {
    // funcao que move o projetil ao inimigo e checa colisao

    std::shared_ptr<Enemy> enemy = _target.lock();

    // mantem a direcao caso o target seja perdido
    if (enemy)
        _direction = normalize(enemy->get_position() - _position);

    _position += (float)(_speed * dt) * _direction;

    // ve se acertou algum inimigo (pode nao ser o target)
    GameRoom &game_room = dynamic_cast<GameRoom&>(_room);
    if (auto hit = game_room.get_wave_manager().get_enemy_colliding(_position)) {
        on_hit(hit);
        destroy();

        return;
    }

    // saiu da tela
    if (!GAME_RECT.contains(_position))
        destroy();
}

void TroopProjectile::on_hit(std::shared_ptr<Enemy> enemy) {
    if (enemy) {
        //Comportamento default: so da dano
        enemy->damage(_damage * GameManager::get_instance().get_troop_damage_multiplier());
    }
}