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
    int _price;
    Room &_room;

public:
    TroopCard(sf::Vector2f position, float _width, TroopType _troop, int price, Room &room);

    /// Checa se uma posicao esta dentro dessa carta (util pra detectar o mouse dentro)
    bool position_meeting(sf::Vector2f position);

    void draw();

    TroopType get_troop();

    /// Retorna o tipo da tropa e gasta os pontos se tiver, se nao tiver pontos retorna None
    TroopType buy();
};

#endif