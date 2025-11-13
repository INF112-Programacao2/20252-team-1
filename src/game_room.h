#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "troop_manager.h"
#include "wall.h"
#include "wave_manager.h"

class GameRoom : public Room {
private:
    TroopManager _troop_manager;
    WaveManager _wave_manager;
    sf::Font &_font;
    Wall _wall;

public:
    GameRoom(sf::RenderWindow &window, RoomManager &room_manager, int base_life, int spike_damage);

    ~GameRoom();

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void end();

    WaveManager &get_wave_manager();
    Wall &get_wall();
};

#endif