#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "game_saver.h"

class GameRoom;

class GameManager {
private:
    int _points = 0;
    double _cooldown_multiplier = 1.0;     // entre 0-1, quanto menor mais rapido o cooldown
    double _damage_multiplier = 1.0;       // quanto maior mais dano os inimigos sofrem
    double _troop_damage_multiplier = 1.0; // quanto maior mais dano as tropas dao nos inimigos
    double _point_multiplier = 1.0;        // quanto maior o valor, maior a pontuacao final
    int _crit_chance = 0;                  // quanto maior o valor, maior a chance de critico
    sf::Font _font;
    GameRoom *_game_room = nullptr;
    GameSaver *_game_saver;

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

    void set_points(int points);
    void add_points(int points);

    double get_cooldown_multiplier();
    void set_cooldown_multiplier(double cooldown_multiplier);

    double get_damage_multiplier();
    void set_damage_multiplier(double damage_multiplier);

    double get_troop_damage_multiplier();
    void set_troop_damage_multiplier(double troop_damage_multiplier);

    double get_point_multiplier();
    void set_point_multiplier(double point_multiplier);

    int get_crit_chance();
    void set_crit_chance(int chance);

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

    void set_game_room(GameRoom *room);
    GameRoom &get_game_room();

    void set_game_saver(GameSaver *game_saver);
    GameSaver *get_game_saver();
};

#endif