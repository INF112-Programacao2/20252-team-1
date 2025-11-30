#include "wave_manager.h"
#include "fire_enemy.h"
#include "lumberjack_enemy.h"
#include "hunter_enemy.h"
#include "excavator_enemy.h"
#include "trashman_enemy.h"
#include "businessman_enemy.h"
#include "trash_enemy.h"
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
    // wave 1:
    // probabilidades, numero de inimigos, delay entre inimigos, delay pra terminar subwave
    SubWave subwave_01 = {{0, 1, 0, 0, 0, 0, 0, 0}, 4, 0, 3};
    SubWave subwave_02 = {{0, 1, 0, 0, 0, 0, 0, 0}, 4, 0, 3};
    SubWave subwave_03 = {{0, 1, 0, 0, 0, 0, 0, 0}, 4, 0, 3};
    _enemys_layout[0] = {subwave_01, subwave_02, subwave_03};

    spawn_wave();
}

WaveManager::~WaveManager() = default;

void WaveManager::spawn_enemy(EnemyType enemy_type, int line) {
    switch (enemy_type) {
    case EnemyType::Enemy1:
        // vida, dano, linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<Enemy>(75, 10, line, 50.0, 5.0, 10, _room));
        break;

    case EnemyType::Lumberjack:
        // vida, dano, linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<LumberjackEnemy>(150, 25, line, 50.0, 3.0, 20, _room));
        break;

    case EnemyType::FireEnemyType:
        // vida, dano, linha, velocidade, cooldown, pontos, burn_timer, sala
        _enemys.push_back(std::make_shared<FireEnemy>(100, 15, line, 150.0, 0, 15, 2, _room));
        break;

    case EnemyType::Hunter:
        // vida, dano, linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<HunterEnemy>(75, 20, line, 50.0, 6.0, 30, _room));
        break;

    case EnemyType::Excavator:
        // vida, dano , linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<ExcavatorEnemy>(300, 1, line, 30.0, 1, 50, _room));
        break;

    case EnemyType::Trashman:
        // vida, dano , linha, velocidade, cooldown, pontos, sala
        _enemys.push_back(std::make_shared<TrashmanEnemy>(200, 35, line, 40.0, 5.0, 60, _room));
        break;

    case EnemyType::Businessman:
        // vida, dano , linha, velocidade, cooldown, cura, raio de cura, pontos, sala
        _enemys.push_back(std::make_shared<BusinessmanEnemy>(100, 5, line, 60.0, 4.0, 5, 200, 80, _room));
        break;
    case EnemyType::Trash:
        // nao spawna lixo diretamente
        break;

    default:
        std::cerr << "Inimigo com ID: " << enemy_type << " nao implementado!" << std::endl;
        break;
    }
}

void WaveManager::spawn_wave() {
    spawn_enemy(EnemyType::Trashman, 1);
    spawn_enemy(EnemyType::Businessman, 2);
    spawn_enemy(EnemyType::Lumberjack, 3);
    spawn_enemy(EnemyType::Hunter, 4);
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

    // delay ate a proxima wave
    double delay = 0;

    // verifica o fim da subwave e atualiza pra proxima
    if (!_is_waiting_delay && _enemys.size() == 0) {
        _is_waiting_delay = true;
        delay = _enemys_layout[_wave_idx][_subwave_idx].ending_delay;

        _subwave_idx++;
        if (_subwave_idx >= 3) {
            _subwave_idx = 0;
            _wave_idx++;
            delay = _wave_ending_delay;
        }

        // TODO: mostrar que ganhou o jogo
        if (_wave_idx >= MAX_WAVES) {
            _wave_idx = MAX_WAVES; // nao deixa dar overflow no array por enquanto
            return;
        }
    }

    if (_is_waiting_delay) {
        _timer.update(dt);

        if (_timer.get_seconds_elapsed() >= delay) {
            spawn_wave();
            _timer.restart();
            _is_waiting_delay = false;
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
    _wave_idx = wave_idx;
}