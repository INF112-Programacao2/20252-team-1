#include "game_saver.h"
#include "troop.h"
#include <iostream>
#include <sstream>

GameSaver::GameSaver(const std::string &save_file_path) : _save_file_path(save_file_path) {
    // valores default
    _wave_idx = 0;
    _points = 1000;
    _wall_life = 1000;
    for (auto &troop_type : _troops) {
        troop_type = TroopType::None;
    }

    //TODO: valores default para upgrades
}

void GameSaver::save() {
    _save_file.open(_save_file_path, std::ios::out);

    if (!_save_file.is_open()) {
        std::cerr << "Nao foi possivel criar o arquivo de save, continuando sem salvar o jogo!" << std::endl;
        return;
    }

    // salva as informacoes no arquivo
    _save_file << _wave_idx << ' ' << _points << ' ' << _wall_life << std::endl;

    for (int i = 0; i < _troops.size() - 1; i++)
        _save_file << _troops[i] << ' ';
    _save_file << _troops.back() << std::endl;

    _save_file << _field_troops.size() << std::endl;

    for (auto &[type, pos] : _field_troops) {
        _save_file << type << ' ' << pos.x << ' ' << pos.y << std::endl;
    }

    //TODO: salvar upgrades
    _save_file.close();
}

void GameSaver::load() {
    _save_file.open(_save_file_path);
    if (!_save_file.is_open()) {
        // Nao possui arquivo de save ainda, saindo
        return;
    }

    // atualiza variaveis
    _save_file >> _wave_idx >> _points >> _wall_life;

    for (int i = 0; i < _troops.size(); i++) {
        int type;
        _save_file >> type;
        _troops[i] = (TroopType)type;
    }

    int size;
    _save_file >> size;

    _field_troops.resize(size);
    for (int i = 0; i < size; i++) {
        int type;
        _save_file >> type;

        sf::Vector2f position;
        _save_file >> position.x >> position.y;
        _field_troops[i] = std::make_pair((TroopType)type, position);
    }

    //TODO: carregar upgrades
    _save_file.close();
}

int GameSaver::get_wave_idx() const {
    return _wave_idx;
}

void GameSaver::set_wave_idx(int wave_idx) {
    _wave_idx = wave_idx;
}

int GameSaver::get_points() const {
    return _points;
}

void GameSaver::set_points(int points) {
    _points = points;
}

int GameSaver::get_wall_life() const {
    return _wall_life;
}

void GameSaver::set_wall_life(int wall_life) {
    _wall_life = wall_life;
}

std::array<TroopType, TROOP_ROWS * TROOP_COLS> GameSaver::get_troops() const {
    return _troops;
}

void GameSaver::set_troops(std::array<TroopType, TROOP_ROWS * TROOP_COLS> troops) {
    _troops = troops;
}

const std::vector<std::pair<TroopType, sf::Vector2f>> &GameSaver::get_field_troops() const {
    return _field_troops;
}

void GameSaver::set_field_troops(const std::vector<FieldTroop*> &field_troops) {
    _field_troops.clear();
    for (FieldTroop* field_troop : field_troops) {
        _field_troops.emplace_back(field_troop->get_type(), field_troop->get_position());
    }
}
