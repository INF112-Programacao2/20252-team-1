#include "game_manager.h"
#include "globals.h"
#include <cmath>
#include <stdexcept>

void GameManager::reset() {
    _points = BASE_START_POINTS;
    _cooldown_multiplier = 1.0;
    _damage_multiplier = 1.0;
    _troop_damage_multiplier = 1.0;
    _point_multiplier = 1.0;
    _crit_chance = 0;
    _special_ability_multiplier = 1.0;

    get_game_room().get_wall().set_max_life(BASE_WALL_LIFE);
    get_game_room().get_wall().set_life(BASE_WALL_LIFE);
    get_game_room().get_wall().set_spike_damage(0);
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

double GameManager::get_special_ability_multiplier() {
    return _special_ability_multiplier;
}

void GameManager::set_special_ability_multiplier(double value) {
    _special_ability_multiplier = value;
}

double GameManager::get_point_multiplier() {
    return _point_multiplier;
}

sf::Font &GameManager::get_font() {
    return _font;
}

// atualizacao do error handling
void GameManager::load_font(std::string file_path) {
    if (!_font.loadFromFile(file_path)) {
        throw std::runtime_error("Falha em carregar a fonte de " + file_path);
    }
}

// implementacao dos metodos de audio

void GameManager::load_musics() {
    if (!_menu_music.openFromFile("assets/menu principal.ogg")) {
        throw std::runtime_error("Erro carregando musica: assets/menu principal.ogg");
    }
    if (!_game_music.openFromFile("assets/jogo principal.ogg")) {
        throw std::runtime_error("Erro carregando musica: assets/jogo principal.ogg");
    }
    if (!_victory_music.openFromFile("assets/vitoria.ogg")) {
        throw std::runtime_error("Erro carregando musica: assets/vitoria.ogg");
    }
    if (!_defeat_music.openFromFile("assets/derrota.wav")) {
        throw std::runtime_error("Erro carregando musica: assets/derrota.wav");
    }

    // configuracao de loops das musicas
    _menu_music.setLoop(true);
    _menu_music.setVolume(_volume);
    _game_music.setLoop(true);
    _game_music.setVolume(_volume);
    _victory_music.setLoop(false);
    _victory_music.setVolume(_volume);
    _defeat_music.setLoop(false);
    _defeat_music.setVolume(_volume);
}

void GameManager::stop_all_music() {
    _menu_music.stop();
    _game_music.stop();
    _victory_music.stop();
    _defeat_music.stop();
}

void GameManager::play_menu_music() {
    // para as outras musicas -> deve ter um metodo melhor pra isso mas sla
    _game_music.stop();
    _victory_music.stop();
    _defeat_music.stop();

    if (_menu_music.getStatus() != sf::Music::Playing) {
        _menu_music.play();
    }
}

void GameManager::play_game_music() {
    _menu_music.stop();
    _victory_music.stop();
    _defeat_music.stop();

    // se for pra upgrade room a musica continua
    if (_game_music.getStatus() != sf::Music::Playing) {
        _game_music.play();
    }
}

float GameManager::get_music_volume() {
    return _volume;
}

void GameManager::set_music_volume(float volume) {
    _volume = volume;

    _menu_music.setVolume(_volume);
    _game_music.setVolume(_volume);
    _victory_music.setVolume(_volume);
    _defeat_music.setVolume(_volume);
}

void GameManager::increase_volume(float volume) {
    _volume = std::min(100.f, _volume + volume);

    _menu_music.setVolume(_volume);
    _game_music.setVolume(_volume);
    _victory_music.setVolume(_volume);
    _defeat_music.setVolume(_volume);
}

void GameManager::decrease_volume(float volume) {
    _volume = std::max(0.f, _volume - volume);

    _menu_music.setVolume(_volume);
    _game_music.setVolume(_volume);
    _victory_music.setVolume(_volume);
    _defeat_music.setVolume(_volume);
}

void GameManager::pause_game_music() {
    if (_game_music.getStatus() == sf::Music::Playing) {
        _game_music.pause();
    }
}

void GameManager::resume_game_music() {
    if (_game_music.getStatus() == sf::Music::Paused) {
        _game_music.play();
    }
}

void GameManager::play_victory_music() {
    _game_music.stop();
    if (_victory_music.getStatus() != sf::Music::Playing) {
        _victory_music.play();
    }
}

void GameManager::play_defeat_music() {
    _game_music.stop();
    if (_defeat_music.getStatus() != sf::Music::Playing) {
        _defeat_music.play();
    }
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

void GameManager::set_game_room(GameRoom *room) {
    _game_room = room;
}

GameRoom &GameManager::get_game_room() {
    return *_game_room;
}

void GameManager::set_game_saver(GameSaver *game_saver) {
    _game_saver = game_saver;
}

GameSaver *GameManager::get_game_saver() {
    return _game_saver;
}