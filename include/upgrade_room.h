#ifndef UPGRADE_ROOM_H
#define UPGRADE_ROOM_H

#include <SFML/Graphics.hpp>
#include <array>
#include "room.h"
#include "upgradeUI.h"
#include "globals.h"

class UpgradeRoom : public Room {
private:
    sf::Font _font;
    std::array<UpgradeUI, UPGRADE_COUNT> _upgrades; //! mudar a quantidade no "globals.h"
    sf::Texture _hud_background;

public:
    UpgradeRoom(sf::RenderWindow &window, RoomManager &room_manager);

    ~UpgradeRoom();

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue) override;

    void end();

    std::array<int, UPGRADE_COUNT> get_upgrade_levels() const;
    void set_upgrade_levels(std::array<int, UPGRADE_COUNT> levels);
};

#endif
