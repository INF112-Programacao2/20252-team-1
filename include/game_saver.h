#ifndef GAME_SAVER_H
#define GAME_SAVER_H

#include "globals.h"
#include "field_troop.h"
#include "game_room.h"
#include "upgrade_room.h"
#include <array>
#include <vector>
#include <fstream>
#include <string>

/*
EXEMPLO DE UM ARQUIVO DE SAVE:

5 1000 300 // "wave_idx", "points" e "wall_life"
-1 0 -1 -1 0 -1 -1 -1 2 2 // array de TroopTypes nas posições
0 0 0 0 0 // array de nivel dos upgrades comprados na ordem do array
3 // tamanho do vetor "field_troops"
9 600 500.23  // TroopType e posicao x e y
9 1000 500.23 // TroopType e posicao x e y
9 1000 800.51 // TroopType e posicao x e y
*/

class GameSaver {
private:
    int _wave_idx, _points, _wall_life;
    std::array<int, UPGRADE_COUNT> _upgrades;
    std::array<TroopType, TROOP_ROWS * TROOP_COLS> _troops;
    std::vector<std::pair<TroopType, sf::Vector2f>> _field_troops;
    std::string _save_file_path;
    std::fstream _save_file;
    GameRoom& _game_room;
    UpgradeRoom& _upgrade_room;

private:
    /// Atualiza o jogo com o estado atual da classe
    void update_game_state();

    /// Atualiza a classe com o estado atual do jogo
    void load_game_state();

public:
    GameSaver(const std::string &save_file_path, GameRoom& game_room, UpgradeRoom& upgrade_room);

    /// Salva o estado atual DO JOGO para o arquivo e salva na classe
    void save();

    /// Modifica o estado da classe E DO JOGO com o que foi salvo no arquivo
    void load();

    int get_wave_idx() const;
    void set_wave_idx(int wave_idx);

    int get_points() const;
    void set_points(int points);

    int get_wall_life() const;
    void set_wall_life(int wall_life);

    std::array<TroopType, TROOP_ROWS * TROOP_COLS> get_troops() const;
    void set_troops(std::array<TroopType, TROOP_ROWS * TROOP_COLS> troops);

    const std::vector<std::pair<TroopType, sf::Vector2f>> &get_field_troops() const;
    void set_field_troops(const std::vector<FieldTroop*> &field_troops);
};

#endif