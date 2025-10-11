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
};

const int TROOP_COUNT = 6;
const int TROOP_PRICES[TROOP_COUNT] = {300, 300, 300, 300, 300, 300};

const sf::Vector2u DESKTOP_SIZE = sf::Vector2u(
    sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

const int GAME_SIZE_X = sf::VideoMode::getDesktopMode().width - 400;

const int TROOP_ROWS = 4;
const int TROOP_COLS = 3;

#endif