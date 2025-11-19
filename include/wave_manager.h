#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "enemy.h"
#include "clock.h"
#include "globals.h"
#include "enemy_projectile.h"
#include <memory>
#include <array>
#include <vector>
#include <unordered_set>

struct SubWave {
    std::array<float, ENEMY_COUNT> probabilities; // uma pra cada tipo de inimigo
    int num_enemys;                               // numero de inimigos da subwave
    double spawn_delay;                           // delay entre spawn de inimigos
    double ending_delay;                          // delay pra terminar a subwave
};

const int MAX_WAVES = 1;

class WaveManager {
private:
    int _wave_idx = 0;
    int _subwave_idx = 0;
    std::unordered_set<std::shared_ptr<Enemy>> _enemys;
    std::unordered_set<std::unique_ptr<EnemyProjectile>> _projectiles;
    std::array<std::array<SubWave, 3>, MAX_WAVES> _enemys_layout; // 3 subwaves por wave
    double _wave_ending_delay = 8;                                // delay entre waves
    bool _is_waiting_delay = false;
    Clock _timer;
    Room &_room;

private:
    void spawn_wave();

public:
    WaveManager(Room &room);

    ~WaveManager();

    void run(double dt);

    void draw();

    void spawn_projectile(std::unique_ptr<EnemyProjectile> projectile);

    /// Retorna o inimigo mais proximo da posicao especificada (pode retornar ponteiro vazio)
    std::shared_ptr<Enemy> get_closest_enemy(sf::Vector2f position);

    /// Retorna o inimigo mais proximo na linha (pode ponteiro vazio)
    std::shared_ptr<Enemy> get_closest_enemy_on_line(int line);

    /// Retorna todos os inimigos dentro do circulo
    std::vector<std::shared_ptr<Enemy>> get_enemys_on_circle(sf::Vector2f center, float radius);

    void remove_enemy(Enemy *enemy);
};

#endif