#ifndef TROOP_MANAGER_H
#define TROOP_MANAGER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "room.h"
#include "troop_card.h"
#include "globals.h"

class TroopManager {
private:
    Room &_room;
    std::array<TroopCard *, TROOP_COUNT> _shop_cards;

private:
    int position_to_slot(sf::Vector2f position);

    sf::RenderWindow &get_window();

    sf::Vector2f get_mouse_pos();

public:
    TroopManager(Room &room);

    ~TroopManager();

    void run(double _dt, const std::vector<sf::Event> &event_queue);

    void draw_slots();

    void draw_shop();
};

#endif