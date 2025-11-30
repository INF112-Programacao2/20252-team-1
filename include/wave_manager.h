#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "clock.h"
#include "globals.h"
#include "enemy_projectile.h"
#include "enemy.h"
#include <memory>
#include <array>
#include <vector>

struct SubWave {
    int enemy_count;      // numero de inimigos na subwave
    float spawn_interval; // tempo entre cada spawn dentro da subwave
    std::array<float, ENEMY_COUNT> probabilities; // array de probabilidade de cada inimigo
};

const int MAX_WAVES = 4;

const int SUBWAVES_PER_WAVE = 3;

class WaveManager {
private:
    std::vector<std::shared_ptr<Enemy>> _enemys;
    std::vector<std::unique_ptr<EnemyProjectile>> _projectiles;

    // matriz de subwaves
    std::array<std::array<SubWave, SUBWAVES_PER_WAVE>, MAX_WAVES> _waves_config;

    int _wave_idx = 0;           // wave atual
    int _subwave_idx = 0;        // subwave atual
    int _spawned_in_subwave = 0; // quantos ja nasceram na subwave atual
    
    // estados
    bool _is_spawning = true;              // se estamos na fase de jogar inimigos na tela
    bool _is_waiting_next_subwave = false; // se estamos no intervalo entre subwaves
    bool _game_completed = false;

    // constantes de tempo
    const double DELAY_BETWEEN_SUBWAVES = 2.0;
    const double DELAY_BETWEEN_WAVES = 5.0;

    Clock _timer;
    Room &_room;

private:
    void spawn_enemy(EnemyType enemy_type, int line);

    // configura todas as porcentagens e numeros de inimigos
    void setup_waves();

    // sorteia um inimigo baseado nas porcentagens da subwave atual
    EnemyType pick_weighted_enemy(const std::array<float, ENEMY_COUNT> &probs);

public:
    WaveManager(Room &room);

    ~WaveManager();

    void run(double dt);

    void draw();

    void spawn_projectile(std::unique_ptr<EnemyProjectile> projectile);

    void add_enemy(std::shared_ptr<Enemy> enemy); // pro trashman

    // retorna o inimigo mais proximo da posicao especificada (pode retornar ponteiro vazio)
    std::shared_ptr<Enemy> get_closest_enemy(sf::Vector2f position);

    // retorna o inimigo mais proximo na linha (pode ponteiro vazio)
    std::shared_ptr<Enemy> get_closest_enemy_on_line(int line);

    // retorna todos os inimigos dentro do circulo
    std::vector<std::shared_ptr<Enemy>> get_enemys_on_circle(sf::Vector2f center, float radius);

    // retorna o primeiro inimigo que colide com a posicao
    std::shared_ptr<Enemy> get_enemy_colliding(sf::Vector2f position);

    int get_wave_idx(); // +1 pra mostrar na UI

    void set_wave_idx(int wave_idx);
};

#endif