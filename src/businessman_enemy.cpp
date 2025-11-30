#include "businessman_enemy.h"
#include "game_room.h"
#include "visual_effect.h"
#include <cmath>
#include <iostream>

sf::Texture BusinessmanEnemy::_texture;
sf::Texture BusinessmanEnemy::_projectile_texture;

const float height = 100;

// o hunter para em 400 entao 250 faz o Businessman chegar mais perto
const float ATTACK_RANGE = 250.0f;

BusinessmanEnemy::BusinessmanEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int heal_amount, double heal_radius, int points, Room& room)
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room) {

    _heal_radius = heal_radius;
    _heal_amount = heal_amount;
    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setSize({ width, height });
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    _shape.setPosition(get_position());
}

bool BusinessmanEnemy::can_walk(double next_position) {
    return next_position > (WALL_POSITION_X + WALL_WIDTH + ATTACK_RANGE);
}

void BusinessmanEnemy::run(double dt) {
    Enemy::run(dt);

    // logica da sequencia rapida de tiros
    if (_is_attacking) {
        _rapid_fire_timer.update(dt);

        if (_rapid_fire_timer.timeout()) {
            fire_projectile();
            heal_allies();

            _shots_fired++;

            // intervalo entre tiros na sequencia
            _rapid_fire_timer.set_timeout_duration(0.15);
            _rapid_fire_timer.restart();

            if (_shots_fired >= 4) {
                _is_attacking = false;
            }
        }
    }
}

void BusinessmanEnemy::draw() {
    _shape.setTexture(&_texture);
    Enemy::draw();
}

void BusinessmanEnemy::attack() {
    // inicia a sequencia de ataque
    _is_attacking = true;
    _shots_fired = 0;

    // forca o primeiro tiro a sair imediatamente
    _rapid_fire_timer.set_timeout_duration(0);
    _rapid_fire_timer.restart();
}

void BusinessmanEnemy::fire_projectile() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    auto projectile = std::make_unique<EnemyProjectile>(
        get_position(),
        shared_from_this(),
        game_room.get_wall(),
        _damage,
        250.0, // velocidade
        _room,
        ProjectileType::EnemyBaseProjectile 
    );

    projectile->set_texture(&_projectile_texture, 30.f);

    // calculo do angulo -> 4 tiros espacados em 12 graus
    double angle_deg = 180.0 + (_shots_fired * 12.0 - 20.0);
    double angle_rad = angle_deg * 3.14159 / 180.0;

    projectile->set_direction(sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)));

    game_room.get_wave_manager().spawn_projectile(std::move(projectile));
}

void BusinessmanEnemy::heal_allies() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    // verde translucido
    game_room.add_effect(std::make_unique<VisualEffect>(
        get_position(), _heal_radius, 0.5, sf::Color(50, 255, 50, 30), _room
    ));

    // pega todos os inimigos no raio
    auto allies = game_room.get_wave_manager().get_enemys_on_circle(get_position(), _heal_radius);

    for (auto& ally : allies) {
        // cura inclusive a si mesmo
        ally->heal(_heal_amount);
    }
}

bool BusinessmanEnemy::load_texture(const std::string& file_path) {
    return _texture.loadFromFile(file_path);
}

bool BusinessmanEnemy::load_projectile_texture(const std::string& file_path) {
    return _projectile_texture.loadFromFile(file_path);
}