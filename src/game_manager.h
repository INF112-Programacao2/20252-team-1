#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class GameManager {
private:
    int _points = 1000;
    double _cooldown_multiplier = 1.0; // entre 0-1, quanto menor mais rapido o cooldown

private:
    GameManager();

    ~GameManager() {}

public:
    static GameManager& get_instance() {
        static GameManager instance;
        return instance;
    }

    int get_points() {
        return _points;
    }

    bool remove_points(int points) {
        if (_points >= points) {
            _points -= points;
            return true;
        }

        return false;
    }

    void add_points(int points) {
        _points += points;
    }

    double get_cooldown_multiplier() {
        return _cooldown_multiplier;
    }

    void set_cooldown_multiplier(double cooldown_multiplier) {
        _cooldown_multiplier = cooldown_multiplier;
    }

    // garante que nao vai ter copias
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};

#endif