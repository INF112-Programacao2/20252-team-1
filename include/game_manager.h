#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

class GameManager {
private:
    int _points = 0;
    double _cooldown_multiplier = 1.0; // entre 0-1, quanto menor mais rapido o cooldown
    double _damage_multiplier = 1.0;   // quanto maior mais dano da nos inimigos
    sf::Font _font;

private:
    GameManager() {}

    ~GameManager() {}

public:
    static GameManager &get_instance() {
        static GameManager instance;
        return instance;
    }

    int get_points();

    /// Retorna true se puder remover e false se nao tiver pontos suficientes
    bool remove_points(int points);

    void add_points(int points);

    double get_cooldown_multiplier();
    void set_cooldown_multiplier(double cooldown_multiplier);

    double get_damage_multiplier();
    void set_damage_multiplier(double damage_multiplier);

    sf::Font &get_font();
    bool load_font(std::string file_path);

    /// Retorna o indice da linha mais proxima, comecando do 0
    static int get_line(sf::Vector2f position);

    /// Retorna a posicao com o y fixado na linha mais proxima
    static sf::Vector2f get_line_pos(sf::Vector2f position);
    /// Retorna a posicao y da linha
    static float get_line_pos(int line);

    // garante que nao vai ter copias
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;
};

#endif