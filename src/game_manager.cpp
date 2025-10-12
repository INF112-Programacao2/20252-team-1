#include "game_manager.h"

int GameManager::get_points() {
    return _points;
}

bool GameManager::remove_points(int points) {
    if (_points >= points) {
        _points -= points;
        return true;
    }

    return false;
}

void GameManager::add_points(int points)  {
    _points += points;
}

double GameManager::get_cooldown_multiplier() {
    return _cooldown_multiplier;
}

void GameManager::set_cooldown_multiplier(double cooldown_multiplier) {
    _cooldown_multiplier = cooldown_multiplier;
}