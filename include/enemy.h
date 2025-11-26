#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "room.h"
#include "health_manager.h"
#include "clock.h"

class Enemy : public std::enable_shared_from_this<Enemy> {
protected:
    HealthManager _health;
    int _damage;
    int _line; // comeca do 1
    double _speed;
    double _speed_multiplier = 1.0;
    Clock _slowdown_timer;
    double _position_x;
    double _base_cooldown;
    double _cooldown;
    int _points;
    sf::Rect<float> _collider;
    // vector<Effect> _effects; // vector de enum de efeitos
    // std::array<double, EFFECT_COUNT> _effect_times; // array de tempo restante de cada efeito
    Room &_room;
    sf::RectangleShape _shape;
    Clock _flash_timer;

protected:
    /// E chamado quando a vida chega a 0
    virtual void destroy();

    virtual bool can_walk(double next_position);

    virtual void attack();

public:
    Enemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room);

    virtual ~Enemy();

    virtual void run(double dt);

    virtual void draw();

    void apply_slowdown(double pct, double duration); // pct entre 0-1 pro macaco

    /// Verifica se a posicao colide com o inimigo
    bool collide(sf::Vector2f position);

    bool is_destroyed();

    int get_line();

    sf::Vector2f get_position();

    // void set_effect(Effect effect, double time); // Ignorar por enquanto -> ignorar pra sempre

    /// Ja multiplica o dano pelo multiplicador, nao precisa multiplicar antes
    void damage(int life);
};

#endif