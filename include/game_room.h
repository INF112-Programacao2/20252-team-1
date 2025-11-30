#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/Graphics.hpp>
#include "troop_manager.h"
#include "wave_manager.h"
#include "wall.h"
#include "room.h"

class GameRoom : public Room {
private:
    sf::Texture _background;
    sf::Texture _background2;
    sf::Texture _hud_background;
    TroopManager _troop_manager;
    WaveManager _wave_manager;
    sf::Font &_font;
    Wall _wall;

public:
    GameRoom(sf::RenderWindow &window, RoomManager &room_manager);

    ~GameRoom();

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void end();

    TroopManager &get_troop_manager();
    WaveManager &get_wave_manager();
    Wall &get_wall();
};

#endif