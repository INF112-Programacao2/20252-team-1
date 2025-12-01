#include "game_manager.h"
#include "globals.h"
#include <cmath>

void GameManager::reset() {
    _points = 0;
    _cooldown_multiplier = 1.0;
    _damage_multiplier = 1.0;
    _troop_damage_multiplier = 1.0;
    _point_multiplier = 1.0;
    _crit_chance = 0;
}

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

void GameManager::set_points(int points) {
    _points = points;
}

void GameManager::add_points(int points) {
    int final_points = static_cast<int>(points * _point_multiplier);
    _points += final_points;
}

double GameManager::get_cooldown_multiplier() {
    return _cooldown_multiplier;
}

double GameManager::get_damage_multiplier() {
    return _damage_multiplier;
}

double GameManager::get_troop_damage_multiplier() {
    return _troop_damage_multiplier;
}

int GameManager::get_crit_chance() {
    return _crit_chance;
}

void GameManager::set_crit_chance(int chance) {
    // Garantindo que a chance nunca vai ultrapassar 100%
    if (chance > 100) {
        chance = 100;
    }
    _crit_chance = chance;
}

double GameManager::get_point_multiplier() {
    return _point_multiplier;
}

sf::Font &GameManager::get_font() {
    return _font;
}

bool GameManager::load_font(std::string file_path) {
    return _font.loadFromFile(file_path);
}

void GameManager::set_cooldown_multiplier(double cooldown_multiplier) {
    _cooldown_multiplier = cooldown_multiplier;
}

void GameManager::set_damage_multiplier(double damage_multiplier) {
    _damage_multiplier = damage_multiplier;
}

void GameManager::set_troop_damage_multiplier(double troop_damage_multiplier) {
    _troop_damage_multiplier = troop_damage_multiplier;
}

void GameManager::set_point_multiplier(double point_multiplier) {
    _point_multiplier = point_multiplier;
}

int GameManager::get_line(sf::Vector2f position) {
    int y = position.y - HUD_HEIGHT - PADDING_Y - TROOP_RADIUS - GAP_Y / 2;
    int line = (int)floor(y / GAP_Y);
    return std::max(-1, std::min(TROOP_ROWS - 2, line)) + 2;
}

sf::Vector2f GameManager::get_line_pos(sf::Vector2f position) {
    return sf::Vector2f(position.x, get_line_pos(get_line(position)));
}

float GameManager::get_line_pos(int line) {
    return HUD_HEIGHT + PADDING_Y + TROOP_RADIUS + (line - 1) * GAP_Y;
}

void GameManager::set_game_room(GameRoom* room) {
    _game_room = room;
}

GameRoom& GameManager::get_game_room() {
    return *_game_room;
}

void GameManager::set_game_saver(GameSaver *game_saver) {
    _game_saver = game_saver;
}

GameSaver *GameManager::get_game_saver() {
    return _game_saver;
}