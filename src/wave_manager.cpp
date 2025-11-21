#include "wave_manager.h"

WaveManager::WaveManager(Room &room) : _room(room) {
    // wave 1:
    SubWave subwave_01 = {{1.0}, 4, 0, 3};
    SubWave subwave_02 = {{1.0}, 4, 0, 3};
    SubWave subwave_03 = {{1.0}, 4, 0, 3};
    _enemys_layout[0] = {subwave_01, subwave_02, subwave_03};

    spawn_wave();
}

WaveManager::~WaveManager() = default;

void WaveManager::spawn_wave() {
    _enemys.push_back(std::make_shared<Enemy>(50, 10, 1, 5.0, 25, _room));
    _enemys.push_back(std::make_shared<Enemy>(50, 10, 2, 5.0, 25, _room));
    _enemys.push_back(std::make_shared<Enemy>(50, 10, 3, 5.0, 25, _room));
    _enemys.push_back(std::make_shared<Enemy>(50, 10, 4, 5.0, 25, _room));
}

void WaveManager::run(double dt) {
    // Run dos inimigos
    for (int i = 0; i < _enemys.size(); ) {
        _enemys[i]->run(dt);

        if (_enemys[i]->is_destroyed()) {
            std::swap(_enemys[i], _enemys.back());
            _enemys.pop_back();
        } else
            i++;
    }

    // Run dos projeteis de inimigos
    for (int i = 0; i < _projectiles.size(); ) {
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
    for (const std::shared_ptr<Enemy>& enemy : _enemys) {
        if (enemy->collide(position))
            return enemy;
    }

    return nullptr;
}