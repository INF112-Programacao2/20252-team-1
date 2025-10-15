#ifndef TROOP_H
#define TROOP_H

#include <SFML/Graphics.hpp>
#include "room.h"

//TODO: transformar numa interface
class Troop {
protected:
    sf::Vector2f _position;
    double _cooldown = 2.0;
    sf::Clock _timer;
    Room &_room;

public:
    Troop(sf::Vector2f position, Room &room);
    Troop(sf::Vector2f position, double cooldown, Room &room);

    virtual ~Troop();

    virtual void run(double dt);

    // Ativa a habilidade
    virtual void fire();

    virtual void draw();

    /// Reseta o timer pra quando mudar de janela ou pausar o jogo
    void reset_timer();
};

#endif