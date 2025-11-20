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
    _enemys.insert(std::make_shared<Enemy>(10, 10, 1, 4.0, 25, _room));
    _enemys.insert(std::make_shared<Enemy>(10, 10, 2, 3.0, 25, _room));
    _enemys.insert(std::make_shared<Enemy>(10, 10, 3, 3.0, 25, _room));
    _enemys.insert(std::make_shared<Enemy>(10, 10, 4, 3.5, 25, _room));
}

void WaveManager::run(double dt) {

    for (auto &enemy : _enemys) {
        enemy->run(dt);
    }

    for (auto it = _projectiles.begin(); it != _projectiles.end(); ) {
        it->get()->run(dt);

        if (it->get()->is_destroyed()) {
            it = _projectiles.erase(it);
        } else
            it++;
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
        if (_wave_idx >= MAX_WAVES)
            return;
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
    _projectiles.insert(std::move(projectile));
}

/// Retorna a distancia ao quadrado, util para comparar distancias
float get_distance_sqr(sf::Vector2f a, sf::Vector2f b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

std::shared_ptr<Enemy> WaveManager::get_closest_enemy(sf::Vector2f position) {
    std::shared_ptr<Enemy> closest;
    float min_distance = 1000000;

    for (std::shared_ptr<Enemy> enemy : _enemys) {
        float distance = get_distance_sqr(position, enemy->get_position());
        if (distance < min_distance) {
            closest = enemy;
            min_distance = distance;
        }
    }

    return closest;
}

std::shared_ptr<Enemy> WaveManager::get_closest_enemy_on_line(int line) {
    std::shared_ptr<Enemy> closest;
    float closest_x_pos = 1000000;

    for (std::shared_ptr<Enemy> enemy : _enemys) {
        if (enemy->get_line() == line && enemy->get_position().x < closest_x_pos) {
            closest = enemy;
            closest_x_pos = enemy->get_position().x;
        }
    }

    return closest;
}

std::vector<std::shared_ptr<Enemy>> WaveManager::get_enemys_on_circle(sf::Vector2f center, float radius) {
    std::vector<std::shared_ptr<Enemy>> vec;

    for (std::shared_ptr<Enemy> enemy : _enemys) {
        if (get_distance_sqr(center, enemy->get_position()) <= radius * radius)
            vec.push_back(enemy);
    }

    return vec;
}

void WaveManager::remove_enemy(Enemy *enemy) {
    for (std::shared_ptr<Enemy> sp : _enemys) {
        if (sp.get() == enemy) {
            _enemys.erase(sp);
            break;
        }
    }
}