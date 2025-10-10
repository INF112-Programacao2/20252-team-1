#ifndef TROOP_MANAGER_H
#define TROOP_MANAGER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "room.h"
#include "troop_card.h"
#include "troop.h"
#include "globals.h"

class TroopManager {
private:
    Room &_room;
    std::array<TroopCard *, TROOP_COUNT> _shop_cards;
    std::array<Troop *, (TROOP_ROWS * TROOP_COLS)> _troops;
    TroopType _cursor_troop = TroopType::None;

private:
    int position_to_slot(sf::Vector2f position);

    sf::RenderWindow &get_window();

    sf::Vector2f get_mouse_pos();

    void draw_slots();

    void draw_shop();

    void place_troop();

public:
    TroopManager(Room &room);

    ~TroopManager();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void draw();
};

#endif