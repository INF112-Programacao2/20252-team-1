#include "wave_manager.h"
#include "fire_enemy.h"
#include "lumberjack_enemy.h"
#include "hunter_enemy.h"
#include "excavator_enemy.h"
#include "trashman_enemy.h"
#include "businessman_enemy.h"
#include "trash_enemy.h"
#include "game_manager.h"
#include <iostream>

WaveManager::WaveManager(Room &room) : _room(room) {
    // carregando texturas:
    if (!LumberjackEnemy::load_texture("assets/madeireiro.png")) {
        std::cerr << "Nao achou o asset do madeireiro!\n";
        std::exit(1);
    }

    if (!FireEnemy::load_texture("assets/fogo.png")) {
        std::cerr << "Nao achou o asset do inimigo de fogo!\n";
        std::exit(1);
    }

    if (!HunterEnemy::load_texture("assets/hunter.png")) {
        std::cerr << "Nao achou o asset do hunter!\n";
        std::exit(1);
    }

    if (!HunterEnemy::load_projectile_texture("assets/hunter_projectile.png")) {
        std::cerr << "Nao achou o asset do projetil do hunter!\n";
        std::exit(1);
    }

    if (!ExcavatorEnemy::load_texture("assets/excavator.png")) {
        std::cerr << "Nao achou o asset do excavator!\n";
        std::exit(1);
    }

    if (!TrashmanEnemy::load_texture("assets/caminhao.png")) {
        std::cerr << "Nao achou o asset do poluidor!\n";
        std::exit(1);
    }

    if (!TrashEnemy::load_texture("assets/lixo.png")) {
        std::cerr << "Nao achou o asset do lixo!\n";
        std::exit(1);
    }

    if (!BusinessmanEnemy::load_texture("assets/empresario.png")) {
        std::cerr << "Nao achou o asset do empresario!\n";
        std::exit(1);
    }

    if (!BusinessmanEnemy::load_projectile_texture("assets/dinheiro.png")) {
        std::cerr << "Nao achou o asset do projetil do empresario!\n";
        std::exit(1);
    }

    setup_waves();
}

WaveManager::~WaveManager() = default;

void WaveManager::setup_waves() {
    // explicando o layout do waves config:
    // [index da wave][index da subwave]
    // numero de inimigos da subwave / intervalo entre cada spawn de subwaves /
    // array de probabilidades: lenhador, fogo, cacador, escavador, poluidor, lixo (nao faz diferenca),
    // empresario

    // WAVE 1
    _waves_config[0][0] = {5, 6.0f, {100.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}};  // subwave 1
    _waves_config[0][1] = {8, 5.5f, {80.f, 0.f, 20.f, 0.f, 0.f, 0.f, 0.f}};  // subwave 2
    _waves_config[0][2] = {10, 5.0f, {70.f, 0.f, 30.f, 0.f, 0.f, 0.f, 0.f}}; // subwave 3

    // WAVE 2
    _waves_config[1][0] = {15, 4.5f, {60.f, 10.f, 30.f, 0.f, 0.f, 0.f, 0.f}};
    _waves_config[1][1] = {20, 4.0f, {50.f, 10.f, 30.f, 10.f, 0.f, 0.f, 0.f}};
    _waves_config[1][2] = {22, 3.5f, {40.f, 20.f, 30.f, 10.f, 0.f, 0.f, 0.f}};

    // WAVE 3
    _waves_config[2][0] = {25, 3.0f, {30.f, 30.f, 30.f, 10.f, 0.f, 0.f, 0.f}};
    _waves_config[2][1] = {28, 2.5f, {20.f, 25.f, 25.f, 25.f, 5.f, 0.f, 0.f}};
    _waves_config[2][2] = {30, 2.0f, {10.f, 20.f, 30.f, 25.f, 15.f, 0.f, 0.f}};

    // WAVE 4
    _waves_config[3][0] = {35, 1.5f, {10.f, 20.f, 30.f, 30.f, 10.f, 0.f, 0.f}};
    _waves_config[3][1] = {40, 1.0f, {5.f, 15.f, 30.f, 30.f, 20.f, 0.f, 0.f}};
    _waves_config[3][2] = {50, 0.5f, {5.f, 10.f, 25.f, 30.f, 30.f, 0.f, 0.f}};
}

EnemyType WaveManager::pick_weighted_enemy(const std::array<float, ENEMY_COUNT> &probs) {
    // pra nao precisar colocar numeros que somem exatamente em 100% de probabilidade
    float total_weight = 0;
    for (float p : probs) {
        total_weight += p;
    }

    // sorteia um numero de 0 ate total_weight de forma normalizada
    float random_val = static_cast<float>(rand()) / (float)(RAND_MAX)*total_weight;

    // faz uma soma das probabilidades de cada inimigo e ve se o valor sorteado esta dentro dessa area
    // exemplo: lenhador tem 80 de probabilidade e fogo tem 20, a soma total vai ser 100
    // se o numero sorteado for <= 80, lenhador vai ser spawnado, se cair > 80 e <= 100,
    // o fogo vai ser spawnado
    float current_sum = 0;
    for (int i = 0; i < ENEMY_COUNT; i++) {
        current_sum += probs[i];
        if (random_val <= current_sum) {
            return (EnemyType)i;
        }
    }

    return EnemyType::Lumberjack; // nao e possivel chegar aqui
}

void WaveManager::spawn_enemy(EnemyType enemy_type, int line) {
    // multiplicador de dificuldade que aumenta a cada wave que avanca
    double difficulty_multiplier = 1.0 + (_wave_idx * 0.25);

    switch (enemy_type) {
    case EnemyType::Lumberjack:
        // vida, dano, linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<LumberjackEnemy>(150 * difficulty_multiplier,
                                                            2500 * difficulty_multiplier, line, 50.0, 3.0, 20, _room));
        break;

    case EnemyType::FireEnemyType:
        // vida, dano, linha, velocidade, cooldown, pontos, burn_timer, sala
        _enemys.push_back(std::make_shared<FireEnemy>(100 * difficulty_multiplier,
                                                      15 * difficulty_multiplier, line, 150.0, 0, 15, 2, _room));
        break;

    case EnemyType::Hunter:
        // vida, dano, linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<HunterEnemy>(75 * difficulty_multiplier,
                                                        20 * difficulty_multiplier, line, 50.0, 6.0, 30, _room));
        break;

    case EnemyType::Excavator:
        // vida, dano , linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<ExcavatorEnemy>(300 * difficulty_multiplier,
                                                           1 * difficulty_multiplier, line, 30.0, 1, 50, _room));
        break;

    case EnemyType::Trashman:
        // vida, dano , linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<TrashmanEnemy>(200 * difficulty_multiplier,
                                                          35 * difficulty_multiplier, line, 40.0, 5.0, 60, _room));
        break;

    case EnemyType::Businessman:
        // vida, dano , linha, velocidade, cooldown, cura, raio de cura, pontos, sala
        _enemys.push_back(std::make_shared<BusinessmanEnemy>(100 * difficulty_multiplier,
                                                             5 * difficulty_multiplier, line, 60.0, 4.0, 5 * difficulty_multiplier,
                                                             200 * difficulty_multiplier, 80, _room));
        break;

    case EnemyType::Trash:
        // nao spawna lixo diretamente
        break;

    default:
        std::cerr << "Inimigo com ID: " << enemy_type << " nao implementado!" << std::endl;
        break;
    }
}

void WaveManager::run(double dt) {
    // Run dos inimigos
    for (int i = 0; i < _enemys.size();) {
        _enemys[i]->run(dt);

        if (_enemys[i]->is_destroyed()) {
            std::swap(_enemys[i], _enemys.back());
            _enemys.pop_back();
        } else
            i++;
    }

    // Run dos projeteis de inimigos
    for (int i = 0; i < _projectiles.size();) {
        _projectiles[i]->run(dt);

        if (_projectiles[i]->is_destroyed()) {
            std::swap(_projectiles[i], _projectiles.back());
            _projectiles.pop_back();
        } else
            i++;
    }

    if (_game_completed)
        return;

    _timer.update(dt);

    // pega a configuracao da subwave atual
    const SubWave &config = _waves_config[_wave_idx][_subwave_idx];

    // esperando o intervalo para a proxima subwave
    if (_is_waiting_next_subwave) {
        // se ja matou todos os inimigos, comeca a contar o tempo para a proxima
        if (_enemys.empty()) {
            // define quanto tempo esperar (2 segs entre subwaves e 5 entre waves)
            double delay_necessario;
            if (_subwave_idx == SUBWAVES_PER_WAVE - 1) {
                delay_necessario = DELAY_BETWEEN_WAVES;
            } else {
                delay_necessario = DELAY_BETWEEN_SUBWAVES;
            }

            if (_timer.get_seconds_elapsed() >= delay_necessario) {
                // reseta o estado pra comecara spawnar de novo
                _is_waiting_next_subwave = false;
                _spawned_in_subwave = 0;
                _timer.restart();

                _subwave_idx++; // avanca o indice da subwave

                // se acabaram as subwaves, vai pra proxima wave
                if (_subwave_idx >= SUBWAVES_PER_WAVE) {
                    _subwave_idx = 0;
                    _wave_idx++;

                    if (_wave_idx >= MAX_WAVES) {
                        _game_completed = true;
                        std::cout << "Fim de jogo" << std::endl; //! debug
                        return;
                    } else {
                        // salva o jogo aqui
                        GameManager::get_instance().get_game_saver()->save();
                    }

                    std::cout << "Wave " << _wave_idx + 1 << " iniciada" << std::endl; //! debug
                } else {
                    std::cout << "Subwave " << _subwave_idx + 1 << " iniciada" << std::endl; //! debug
                }
            }
        } else {
            // se ainda tem inimigos vivos, o timer fica travado
            _timer.restart();
        }
        return;
    }

    // bloco pra quando a rodada ta ativa e ainda tem inimigos pra nascer
    if (_is_spawning) {
        if (_spawned_in_subwave < config.enemy_count) {
            // tenta spawnar se passou o intervalo de spawn
            if (_timer.get_seconds_elapsed() >= config.spawn_interval) {
                // sorteia o inimigo
                EnemyType type = pick_weighted_enemy(config.probabilities);
                // sorteia a linha
                int line = (rand() % 4) + 1;

                // spawna o tipo de inimigo sorteado
                spawn_enemy(type, line);

                _spawned_in_subwave++;
                _timer.restart();
            }
        }
        // quando acaba de spawnar tudo dessa subwave, entra no modo espera
        else {
            _is_waiting_next_subwave = true;
            _timer.restart();
        }
    }
}

void WaveManager::draw() {
    for (auto &enemy : _enemys) {
        enemy->draw();
    }

    for (auto &projectile : _projectiles) {
        projectile->draw();
    }
}

void WaveManager::spawn_projectile(std::unique_ptr<EnemyProjectile> projectile) {
    _projectiles.push_back(std::move(projectile));
}

void WaveManager::add_enemy(std::shared_ptr<Enemy> enemy) { // pro trashman
    _enemys.push_back(enemy);
}

/// Retorna a distancia ao quadrado, util para comparar distancias
double get_distance_sqr(sf::Vector2f a, sf::Vector2f b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

std::shared_ptr<Enemy> WaveManager::get_closest_enemy(sf::Vector2f position) {
    if (_enemys.empty())
        return nullptr;

    std::shared_ptr<Enemy> closest = *_enemys.begin();
    double min_distance = get_distance_sqr(position, (*_enemys.begin())->get_position());

    for (const std::shared_ptr<Enemy> &enemy : _enemys) {
        double distance = get_distance_sqr(position, enemy->get_position());
        if (distance < min_distance) {
            closest = enemy;
            min_distance = distance;
        }
    }

    return closest;
}

std::shared_ptr<Enemy> WaveManager::get_closest_enemy_on_line(int line) {
    std::shared_ptr<Enemy> closest;
    float closest_x_pos = 10000000;

    for (const std::shared_ptr<Enemy> &enemy : _enemys) {
        if (enemy->get_line() == line && enemy->get_position().x < closest_x_pos) {
            closest = enemy;
            closest_x_pos = enemy->get_position().x;
        }
    }

    return closest;
}

std::vector<std::shared_ptr<Enemy>> WaveManager::get_enemys_on_circle(sf::Vector2f center, float radius) {
    std::vector<std::shared_ptr<Enemy>> vec;

    for (const std::shared_ptr<Enemy> &enemy : _enemys) {
        if (get_distance_sqr(center, enemy->get_position()) <= radius * radius)
            vec.push_back(enemy);
    }

    return vec;
}

std::shared_ptr<Enemy> WaveManager::get_enemy_colliding(sf::Vector2f position) {
    for (const std::shared_ptr<Enemy> &enemy : _enemys) {
        if (enemy->collide(position))
            return enemy;
    }

    return nullptr;
}

int WaveManager::get_wave_idx() {
    return _wave_idx;
}

void WaveManager::set_wave_idx(int wave_idx) {
    // validacao de seguranca
    if (wave_idx < 0)
        wave_idx = 0;
    if (wave_idx >= MAX_WAVES)
        wave_idx = MAX_WAVES - 1;

    // define a nova wave
    _wave_idx = wave_idx;

    _enemys.clear();

    _projectiles.clear();

    // reseta os estados das subwaves
    _subwave_idx = 0;
    _spawned_in_subwave = 0;

    // reseta os timers e os estados de espera
    _is_waiting_next_subwave = false;
    _is_spawning = true;
    _game_completed = false;
    _timer.restart();
}

bool WaveManager::is_completed() {
    return _game_completed;
}