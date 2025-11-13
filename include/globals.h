#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

// * constantes globais do projeto que fazem sentido compartilhar

enum TroopType {
    None = -1,
    Troop1 = 0,
    Troop2,
    Troop3,
    Troop4,
    Troop5,
    SolarEnergy,
    Hedgehog,
};

const int TROOP_COUNT = 7;
const int TROOP_PRICES[TROOP_COUNT] = {300, 300, 300, 300, 300, 300, 200};

const int ENEMY_COUNT = 1;

const sf::Vector2u DESKTOP_SIZE = sf::Vector2u(
    sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

const int GAME_SIZE_X = sf::VideoMode::getDesktopMode().width - 400;

const int TROOP_ROWS = 4;
const int TROOP_COLS = 3;

const float WALL_POSITION_X = 50 + 175 * 3;
const float WALL_WIDTH = 120;

const float HUD_HEIGHT = DESKTOP_SIZE.y * .1;

const float PADDING_Y = DESKTOP_SIZE.y * 0.1; // espaco vazio em cima e em baixo das tropas
const float TROOP_RADIUS = 75;                // raio do slot
const float GAP_Y = (DESKTOP_SIZE.y - HUD_HEIGHT - 2 * PADDING_Y - 2 * TROOP_RADIUS) / (TROOP_ROWS - 1);

#endif