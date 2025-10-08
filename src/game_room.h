#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include "room.h"
#include "troop_manager.h"

class GameRoom : public Room {
private:
    TroopManager _troop_manager;

public:
    GameRoom(sf::RenderWindow &window);

    ~GameRoom();

    void start() override;

    void run(double dt, const std::vector<sf::Event> &event_queue) override;

    void end() override;
};

#endif