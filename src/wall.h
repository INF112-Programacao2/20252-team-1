#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include "healthmanager.h"
#include "clock.h"
#include "room.h"
#include "enemyprojectile.h"
#include "enemy.h"

class Wall {
private:
    HealthManager _health;
    double _burning_time = 0.0;
    Clock _burning_clock;
    int _spike_damage;
    Rect2 _collider;
    Room& _room;
private:
    void destroy(); // callback do _health
public:
    Wall(int base_life, int spike_damage);

    ~Wall();

    // Recebe dano de um projetil
    void hit(EnemyProjectile& projectile, int damage);
    // Recebe dano de um inimigo
    void hit(Enemy& enemy, int damage);

    // Retorna se a posisao esta colidindo com o muro
    bool collide(Vector2f position) { return _collider.contains(position); }
};

#endif