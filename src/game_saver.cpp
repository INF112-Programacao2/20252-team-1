#include "game_saver.h"
#include "troop.h"
#include "game_manager.h"
#include <iostream>
#include <sstream>

GameSaver::GameSaver(const std::string &save_file_path, GameRoom &game_room, UpgradeRoom &upgrade_room)
    : _save_file_path(save_file_path), _game_room(game_room), _upgrade_room(upgrade_room) {
    // valores default
    _wave_idx = 0;
    _points = 1000;
    _wall_life = 1000;
    for (auto &troop_type : _troops) {
        troop_type = TroopType::None;
    }
    for (auto &value : _upgrades) {
        value = 0;
    }

    update_game_state();
}

void GameSaver::load_game_state() {
    _wave_idx = _game_room.get_wave_manager().get_wave_idx();
    _points = GameManager::get_instance().get_points();
    _wall_life = _game_room.get_wall().get_life();
    _upgrades = _upgrade_room.get_upgrade_levels();
    _troops = _game_room.get_troop_manager().get_troops();
    set_field_troops(_game_room.get_troop_manager().get_field_troops());
}

void GameSaver::update_game_state() {
    _game_room.get_wave_manager().set_wave_idx(_wave_idx);
    GameManager::get_instance().set_points(_points);
    _upgrade_room.set_upgrade_levels(_upgrades); // vem antes do set_life do wall
    _game_room.get_wall().set_life(_wall_life);
    _game_room.get_troop_manager().set_troops(_troops);
    _game_room.get_troop_manager().set_field_troops(_field_troops);
}

void GameSaver::save() {
    _save_file.open(_save_file_path, std::ios::out);

    if (!_save_file.is_open()) {
        std::cerr << "Nao foi possivel criar o arquivo de save, continuando sem salvar o jogo!" << std::endl;
        return;
    }

    load_game_state(); // Carrega as informacoes do jogo

    // salva as informacoes no arquivo:

    // salva inteiros da primeira linha
    _save_file << _wave_idx << ' ' << _points << ' ' << _wall_life << std::endl;

    // salva o tipo das tropas na segunda linha
    for (int i = 0; i < _troops.size() - 1; i++)
        _save_file << _troops[i] << ' ';
    _save_file << _troops.back() << std::endl;

    // salva a quantidade de upgrades comprados para cada tipo na terceira linha
    for (int i = 0; i < UPGRADE_COUNT - 1; i++)
        _save_file << _upgrades[i] << ' ';
    _save_file << _upgrades.back() << std::endl;

    // salva quantas tropas de campo tem na quarta linha
    _save_file << _field_troops.size() << std::endl;

    // salva o tipo + posicao das tropas de campo na quinta linha
    for (auto &[type, pos] : _field_troops) {
        _save_file << type << ' ' << pos.x << ' ' << pos.y << std::endl;
    }

    _save_file.close();

    // Cura as field troops
    _game_room.get_troop_manager().set_field_troops(_field_troops);
}

void GameSaver::load() {
    _save_file.open(_save_file_path);
    if (!_save_file.is_open()) {
        // Nao possui arquivo de save ainda, saindo
        update_game_state(); // atualiza com valores default
        return;
    }

    // atualiza variaveis:

    // le inteiros da primeira linha
    _save_file >> _wave_idx >> _points >> _wall_life;

    // le o tipo das tropas na segunda linha
    for (int i = 0; i < _troops.size(); i++) {
        int type;
        _save_file >> type;
        _troops[i] = (TroopType)type;
    }

    // le a quantidade de upgrades comprados para cada tipo na terceira linha
    for (int i = 0; i < UPGRADE_COUNT; i++)
        _save_file >> _upgrades[i];

    // le quantas tropas de campo tem na quarta linha
    int size;
    _save_file >> size;
    _field_troops.resize(size);

    // le o tipo + posicao das tropas de campo na quinta linha
    for (int i = 0; i < size; i++) {
        int type;
        _save_file >> type;

        sf::Vector2f position;
        _save_file >> position.x >> position.y;
        _field_troops[i] = std::make_pair((TroopType)type, position);
    }

    _save_file.close();

    update_game_state(); // Atualizando o estado do jogo
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

void GameSaver::set_field_troops(const std::vector<FieldTroop *> &field_troops) {
    _field_troops.clear();
    for (FieldTroop *field_troop : field_troops) {
        _field_troops.emplace_back(field_troop->get_type(), field_troop->get_position());
    }
}
