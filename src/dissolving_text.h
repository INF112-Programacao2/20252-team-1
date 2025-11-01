#ifndef DISSOLVING_TEXT_H
#define DISSOLVING_TEXT_H

#include <SFML/Graphics.hpp>
#include "clock.h"
#include "room.h"
#include <string>

class DissolvingText {
private:
    sf::Text _text;
    sf::Vector2f _position;
    double _dissolving_time; // em segundos
    Clock _clock;
    bool _hidden = true; // se vai ser desenhado ou nao
    Room &_room;

public:
    DissolvingText(sf::Vector2f position, double dissolving_time, Room &room);
    DissolvingText(sf::Text text, sf::Vector2f position, double dissolving_time, Room &room);

    void run(double dt);

    void draw();

    void set_text(sf::Text text);

    void set_string(std::string str);

    void set_position(sf::Vector2f position);

    /// Reseta o timer pra fazer o efeito novamente (nao reseta a posicao)
    void restart();
};

#endif