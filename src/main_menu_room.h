#ifndef MAIN_MENU_ROOM_H
#define MAIN_MENU_ROOM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "room.h"
#include "text_button.h"

class MainMenuRoom : public Room {
private:
    sf::Font _font;
    TextButton _start_button;
    TextButton _options_button;
    TextButton _credits_button;
    TextButton _exit_button;

public:
    MainMenuRoom(sf::RenderWindow &window, RoomManager &room_manager);

    ~MainMenuRoom() = default;

    void change_room(std::string room_name);

    void start() {};

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void draw();

    void end() {};
};

#endif