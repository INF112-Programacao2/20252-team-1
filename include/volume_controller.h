#ifndef VOLUME_CONTROLLER_H
#define VOLUME_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "room.h"

class VolumeController {
private:
    sf::Texture _minus_icon;
    sf::Texture _volume_icon;
    sf::Texture _plus_icon;
    bool _minus_hover = false;
    bool _plus_hover = false;
    Room &_room;

public:
    VolumeController(Room &room);

    void run(const std::vector<sf::Event> &event_queue);

    void draw();
};

#endif