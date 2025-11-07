#ifndef MENU_H
#define MENU_H

#include "room.h"
#include "room_manager.h"
#include "text_button.h"
//#include <SMFL/Graphics.hpp>

class Menu : public Room {
private:
    sf::Font _font;
    RoomManager &_manager;
    TextButton _start_button;
    TextButton _exit_button;
    TextButton _credits_button;
    TextButton _options_button;
public:
    Menu(sf::RenderWindow &window);
    ~Menu() override = default;

    void troca_sala();

    void run(double dt);
    void draw();


};

#endif