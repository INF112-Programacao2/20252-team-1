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
    static sf::Texture _texture;

    HealthManager _health;
    double _burning_time = 0.0;
    double _burn_damage_accumulator = 0.0; // acumula dano fracionado do fogo
    double _burn_dps = 0.0;                // dano por segundo do fogo
    Clock _burning_timer;
    int _spike_damage;
    sf::Rect<float> _collider;
    Room &_room;
    Clock _flash_timer;
    sf::RectangleShape _shape;

private:
    void destroy(); // callback do _health
public:
    Wall(int base_life, int spike_damage, Room &room);

    ~Wall();

    void run(double dt);

    void draw();

    // recebe dano de um projetil (tambem pode receber effect)
    void hit(EnemyProjectile &projectile);

    // recebe dano de um inimigo
    void hit(Enemy &enemy, int damage);

    // inicia o efeito de fogo no muro
    void start_burning(double duration, int damage);

    // extingue o fogo no muro
    void extinguish(double duration);

    // retorna se a posicao esta colidindo com o muro
    bool collide(sf::Vector2f position);

    int get_life();
    void set_life(int amount);

    int get_max_life();
    void set_max_life(int max_life);

    // desenha a health bar do muro
    void draw_wall_health_bar();

    void increase_max_life(int amount);

    void increase_life(int amount);

    void increase_spike_damage(int amount);

    static sf::Texture& get_texture();
    static bool load_texture(std::string file_path);
};

#endif