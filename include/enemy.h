#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "room.h"
#include "health_manager.h"

class Enemy : public std::enable_shared_from_this<Enemy> {
protected:
    HealthManager _health;
    int _damage;
    int _line;
    double _position_x;
    double _base_cooldown;
    double _cooldown;
    double _points; // pensar na moeda do jogo logo
    // Rect2 _collider;
    // vector<Effect> _effects; // vector de enum de efeitos
    // std::array<double, EFFECT_COUNT> _effect_times; // array de tempo restante de cada efeito
    Room &_room;
    sf::RectangleShape _shape;

protected:
    virtual void destroy();

    bool can_walk(double next_position);

    virtual void attack();

public:
    Enemy(int base_life, int damage, int line, double base_cooldown, double points, Room &room);

    ~Enemy();

    virtual void run(double dt);

    virtual void draw();

    /// Verifica se a posicao colide com o inimigo
    bool collide(sf::Vector2f position);

    bool is_destroyed() { return _health.is_dead(); }

    int get_line();

    sf::Vector2f get_position();

    // void set_effect(Effect effect, double time); // Ignorar por enquanto

    /// Ja multiplica o dano pelo multiplicador, nao precisa multiplicar antes
    void damage(int life);
};

#endif