#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/Graphics.hpp>
#include "troop_manager.h"
#include "wave_manager.h"
#include "wall.h"
#include "room.h"

class GameRoom : public Room {
private:
    TroopManager _troop_manager;
    WaveManager _wave_manager;
    sf::Font &_font;
    Wall _wall;

public:
    GameRoom(sf::RenderWindow &window, RoomManager &room_manager, int wall_base_life, int wall_spike_damage);

    ~GameRoom();

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void end();

    WaveManager &get_wave_manager();
    Wall &get_wall();
};

#endif