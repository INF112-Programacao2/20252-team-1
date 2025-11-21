#ifndef UPGRADE_ROOM_H
#define UPGRADE_ROOM_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "upgradeUI.h"

class UpgradeRoom : public Room {
private:
    sf::Font _font;
    UpgradeUI _upgrade_ui_1;
    // Outros atributos relacionados ao UpgradeRoom
public:
    UpgradeRoom(sf::RenderWindow &window, RoomManager &room_manager);

    ~UpgradeRoom();

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue) override;

    void end();
};

#endif
