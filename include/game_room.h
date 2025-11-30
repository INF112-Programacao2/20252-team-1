#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "troop_manager.h"
#include "wave_manager.h"
#include "wall.h"
#include "room.h"

// forward declaration para evitar include circular
class VisualEffect;

class GameRoom : public Room {
private:
    sf::Texture _background;
    sf::Texture _background2;
    sf::Texture _hud_background;
    TroopManager _troop_manager;
    WaveManager _wave_manager;
    sf::Font &_font;
    Wall _wall;

    // lista de efeitos visuais ativos
    std::vector<std::unique_ptr<VisualEffect>> _visual_effects;

public:
    GameRoom(sf::RenderWindow &window, RoomManager &room_manager);

    ~GameRoom();

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void end();

    void add_effect(std::unique_ptr<VisualEffect> effect);

    TroopManager &get_troop_manager();
    WaveManager &get_wave_manager();
    Wall &get_wall();
};

#endif