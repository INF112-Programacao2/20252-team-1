#ifndef TROOP_CARD_H
#define TROOP_CARD_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "globals.h"

class TroopCard {
private:
    sf::Vector2f _position;
    float _width;
    TroopType _troop;
    Room &_room;

public:
    TroopCard(sf::Vector2f position, float _width, TroopType _troop, Room &room);

    // checa se uma posicao esta dentro dessa carta (util pra detectar o mouse dentro)
    bool position_meeting(sf::Vector2f position);

    void draw();

    TroopType get_troop();
};

#endif