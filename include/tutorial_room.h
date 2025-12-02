#ifndef TUTORIAL_ROOM_H
#define TUTORIAL_ROOM_H

#include "room.h"
#include <array>

const int SLIDE_COUNT = 6;

class TutorialRoom : public Room {
private:
    std::array<sf::Texture, SLIDE_COUNT> _slides;
    sf::Texture _arrow_texture;
    sf::Sprite _return_arrow;
    sf::RectangleShape _current_slide;
    sf::RectangleShape _left_arrow;
    sf::RectangleShape _left_arrow;
    int _slide_idx = 0;

public:
    TutorialRoom(sf::RenderWindow &window, RoomManager &room_manager);

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void draw();

    void end() {}
};

#endif