#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include "health_manager.h"
#include "clock.h"
#include "room.h"

class EnemyProjectile;
class Enemy;

class Wall {
private:
    HealthManager _health;
    double _burning_time = 0.0;
    Clock _burning_clock;
    int _spike_damage;
    sf::Rect<float> _collider;
    Room &_room;

private:
    void destroy(); // callback do _health
public:
    Wall(int base_life, int spike_damage, Room &room);

    ~Wall();

    void draw();

    // Recebe dano de um projetil (tambem pode receber effect)
    void hit(EnemyProjectile& projectile);

    // Recebe dano de um inimigo
    void hit(Enemy& enemy, int damage) {};

    // Retorna se a posicao esta colidindo com o muro
    bool collide(sf::Vector2f position);

    int get_life();

    void set_life(int amount);

    int get_max_life(); 

    // Desenha a health bar do muro
    void draw_wall_health_bar();

    void increase_max_life(int amount);

    void increase_life(int amount);

    void increase_spike_damage(int amount);
};

#endif