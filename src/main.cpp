#include <SFML/Graphics.hpp>
#include <iostream>
#include "room_manager.h"
#include "game_room.h"
#include "game_manager.h"

int main() {
    //! somente para debug
    const bool FULLSCREEN = true;

    // deixa em tela cheia
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(
        sf::VideoMode(desktop.width, desktop.height),
        "Jogo",
        (FULLSCREEN ? (sf::Style::Titlebar | sf::Style::Close) : 7));

    if (FULLSCREEN)
        window.setPosition(sf::Vector2i(0, 0));
    else
        window.setPosition(sf::Vector2i(50, 50));

    window.setVerticalSyncEnabled(true);

    GameRoom game_room(window);
    RoomManager room_manager("game", &game_room);

    sf::Clock delta_clock; // calcula o delta time (segundos entre o ultimo frame)

    // loop principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //! fecha a janela quando aperta 'R' ou clica no botao (somente debug)
            if ((event.type == sf::Event::Closed) ||
                (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)) {
                window.close();
            }

            room_manager.add_event(event);
        }

        room_manager.run(delta_clock.restart().asSeconds());
    }

    return 0;
}
