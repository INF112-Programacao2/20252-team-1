#include "game_manager.h"
#include "globals.h"
#include <cmath>

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