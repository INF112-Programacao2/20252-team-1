#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class GameManager {
private:
    int _points = 1000;
    double _cooldown_multiplier = 1.0; // entre 0-1, quanto menor mais rapido o cooldown

private:
    GameManager() {}

    ~GameManager() {}

public:
    static GameManager& get_instance() {
        static GameManager instance;
        return instance;
    }

    int get_points();

    /// Retorna true se puder remover e false se nao tiver pontos suficientes
    bool remove_points(int points);

    void add_points(int points);

    double get_cooldown_multiplier();
    void set_cooldown_multiplier(double cooldown_multiplier);

    // garante que nao vai ter copias
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};

#endif