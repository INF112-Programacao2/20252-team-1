#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "troop_manager.h"

class GameRoom : public Room {
private:
    TroopManager _troop_manager;
    sf::Font &_font;

public:
    GameRoom(sf::RenderWindow &window, RoomManager &room_manager);

    ~GameRoom();

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void end();
};

#endif