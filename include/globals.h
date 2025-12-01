#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <array>

// * constantes globais do projeto que fazem sentido compartilhar

enum TroopType {
    None = -1,

    // Troops:
    SolarEnergy = 0,
    Anteater,
    Guard,
    Elephant,
    Squirrel,
    Monkey,
    Dolphin,

    // FieldTroops:
    Hedgehog,
    Tree,
};

// Mudar sempre que adicionar uma troop nova:
const int TROOP_COUNT = 9;
const int TROOP_PRICES[TROOP_COUNT] = {250, 250, 350, 400, 400, 500, 1500, 200, 300};

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

enum EnemyType {
    Lumberjack,
    FireEnemyType,
    Hunter,
    Excavator,
    Trashman,
    Trash,
    Businessman,
};
const int ENEMY_COUNT = 7; // Mudar sempre que aparecer um inimigo novo

const int UPGRADE_COUNT = 7;

const sf::Vector2u DESKTOP_SIZE = sf::Vector2u(
    sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

const int GAME_SIZE_X = sf::VideoMode::getDesktopMode().width - 300;

const sf::Rect<float> GAME_RECT(sf::Vector2f(0, 0), sf::Vector2f(GAME_SIZE_X, DESKTOP_SIZE.y));

const int TROOP_ROWS = 4;
const int TROOP_COLS = 3;

const float WALL_POSITION_X = 50 + 150 * 3;
const float WALL_WIDTH = 150;

const float HUD_HEIGHT = DESKTOP_SIZE.y * .1;

const float PADDING_Y = DESKTOP_SIZE.y * 0.1; // espaco vazio em cima e em baixo das tropas
const float TROOP_RADIUS = 65;                // raio do slot
const float GAP_Y = (DESKTOP_SIZE.y - HUD_HEIGHT - 2 * PADDING_Y - 2 * TROOP_RADIUS) / (TROOP_ROWS - 1);

#endif