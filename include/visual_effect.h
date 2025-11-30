#ifndef VISUAL_EFFECT_H
#define VISUAL_EFFECT_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "clock.h"

class VisualEffect {
private:
    sf::CircleShape _shape;
    sf::Color _start_color;
    double _duration;
    Clock _timer;
    Room& _room;
    bool _finished = false;

public:
    VisualEffect(sf::Vector2f position, float radius, double duration, sf::Color color, Room& room);

    void run(double dt);

    void draw();

    bool is_finished();
};

#endif