#ifndef CREDITS_ROOM_H
#define CREDITS_ROOM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "room.h"
#include "text_button.h"

class CreditsRoom : public Room {
private:
    sf::Font _font;
    sf::Text _title_text;
    sf::Text _credits_text;
    TextButton _menu_button;

public:
    CreditsRoom(sf::RenderWindow &window, RoomManager &room_manager);

    ~CreditsRoom() = default;

    void change_room(std::string room_name);

    void start();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void draw();

    void end() {};
};

#endif