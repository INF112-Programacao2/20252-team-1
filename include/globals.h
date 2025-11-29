#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

// * constantes globais do projeto que fazem sentido compartilhar

enum TroopType {
    None = -1,

    // Troops:
    Anteater = 0,
    Guard,
    Elephant,
    Squirrel,
    Monkey,
    Dolphin,
    SolarEnergy,

    // FieldTroops:
    Hedgehog,
    Tree,
    Troop10,
};

enum ProjectileType {
    EnemyBaseProjectile = 0,
    TroopBaseProjectile,
    AnteaterProjectileType,
    HunterProjectileType,
    ElephantProjectileType,
    SquirrelProjectileType,
    MonkeyProjectileType,
    GuardProjectileType,
    DolphinProjectileType,
};

// Mudar sempre que adicionar uma troop nova:
const int TROOP_COUNT = 10;
const int TROOP_PRICES[TROOP_COUNT] = {200, 350, 350, 300, 300, 300, 250, 200, 300, 300};

enum EnemyType {
    Enemy1 = 0,
    Lumberjack,
    FireEnemyType,
    Hunter,
    Excavator,
    Trashman,
    Trash,
    Businessman,
};
const int ENEMY_COUNT = 8; // Mudar sempre que aparecer um inimigo novo

const int UPGRADE_COUNT = 5;

const sf::Vector2u DESKTOP_SIZE = sf::Vector2u(
    sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

const int GAME_SIZE_X = sf::VideoMode::getDesktopMode().width - 400;

const sf::Rect<float> GAME_RECT(sf::Vector2f(0, 0), sf::Vector2f(GAME_SIZE_X, DESKTOP_SIZE.y));

const int TROOP_ROWS = 4;
const int TROOP_COLS = 3;

const float WALL_POSITION_X = 50 + 175 * 3;
const float WALL_WIDTH = 120;

const float HUD_HEIGHT = DESKTOP_SIZE.y * .1;

const float PADDING_Y = DESKTOP_SIZE.y * 0.1; // espaco vazio em cima e em baixo das tropas
const float TROOP_RADIUS = 75;                // raio do slot
const float GAP_Y = (DESKTOP_SIZE.y - HUD_HEIGHT - 2 * PADDING_Y - 2 * TROOP_RADIUS) / (TROOP_ROWS - 1);

#endif