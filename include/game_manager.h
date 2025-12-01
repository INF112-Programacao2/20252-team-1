#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "game_saver.h"

class GameRoom;

class GameManager {
private:
    int _points = 0;
    double _cooldown_multiplier = 1.0;          // entre 0-1, quanto menor mais rapido o cooldown
    double _damage_multiplier = 1.0;            // quanto maior mais dano os inimigos sofrem
    double _troop_damage_multiplier = 1.0;      // quanto maior mais dano as tropas dao nos inimigos
    double _point_multiplier = 1.0;             // quanto maior o valor, maior a pontuacao final
    int _crit_chance = 0;                       // quanto maior o valor, maior a chance de critico
    double _special_ability_multiplier = 1.0;   // quanto maioro valor, maior a potencia das habilidades das tropas
    sf::Font _font;
    GameRoom *_game_room = nullptr;
    GameSaver *_game_saver;

    // audios
    sf::Music _menu_music;
    sf::Music _game_music;
    sf::Music _victory_music;
    sf::Music _defeat_music;

private:
    GameManager() {}

    ~GameManager() {}

public:
    static GameManager &get_instance() {
        static GameManager instance;
        return instance;
    }

    void reset();

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

    double get_special_ability_multiplier();
    void set_special_ability_multiplier(double value);

    sf::Font &get_font();

    // update para melhor o error handling
    void load_font(std::string file_path);

    // metodos para audio
    void load_musics(); // carrega tudo
    void play_menu_music(); // toca musica do menu
    void play_game_music(); // toca musica do jogo
    void pause_game_music(); // pausa musica do jogo
    void resume_game_music(); // volta musica do jogo
    void play_victory_music(); // toca musica de vitoria
    void play_defeat_music(); // toca musica de derrota
    void stop_all_music(); // para todas as musicas

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