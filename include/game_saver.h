#ifndef GAME_SAVER_H
#define GAME_SAVER_H

#include "globals.h"
#include "field_troop.h"
#include <array>
#include <vector>
#include <fstream>
#include <string>

class GameSaver {
private:
    int _wave_idx, _points, _wall_life;
    std::array<TroopType, TROOP_ROWS * TROOP_COLS> _troops;
    std::vector<std::pair<TroopType, sf::Vector2f>> _field_troops;
    std::string _save_file_path;
    std::fstream _save_file;

public:
    GameSaver(const std::string &save_file_path);

    void save();

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