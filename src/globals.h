#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

// * constantes globais do projeto que fazem sentido compartilhar

enum TroopType {
    Troop1 = 0,
    Troop2,
    Troop3,
    Troop4,
    Troop5,
    Troop6,
};

const int GAME_SIZE_X = sf::VideoMode::getDesktopMode().width - 400;
const int TROOP_COUNT = 6;

#endif