#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept> // novo error handling
#include "room_manager.h"
#include "game_room.h"
#include "game_manager.h"
#include "main_menu_room.h"
#include "upgrade_room.h"
#include "game_saver.h"

int main() {
    std::srand(std::time(0));

    try {
        // carrega a fonte e as musicas no game manager, da throw se falhar
        GameManager::get_instance().load_font("assets/Minecraftia-Regular.ttf");
        GameManager::get_instance().load_musics();
    } catch (const std::exception &e) {
        std::cerr << "ERRO CRITICO: " << e.what() << std::endl;
        return 1;
    }

    const bool FULLSCREEN = true; //! Use false somente para debug
    const bool WINDOWS = false;   //! DEBUG, coloque true se esta compilando para windows

    // deixa em tela cheia
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(
        sf::VideoMode(desktop.width, desktop.height),
        "Jogo",
        (FULLSCREEN ? (WINDOWS ? sf::Style::Fullscreen
                               : (sf::Style::Titlebar | sf::Style::Close))
                    : 7));

    if (FULLSCREEN)
        window.setPosition(sf::Vector2i(0, 0));
    else
        window.setPosition(sf::Vector2i(50, 50));

    window.setVerticalSyncEnabled(true);

    // Criando as salas
    RoomManager room_manager;

    try {
        GameRoom game_room(window, room_manager);
        UpgradeRoom upgrade_room(window, room_manager);

        // Criando o game saver (quem decide se vai carregar ou nao e o main menu)
        GameSaver game_saver("save.txt", game_room, upgrade_room);
        MainMenuRoom main_menu_room(window, room_manager);

        GameManager::get_instance().set_game_saver(&game_saver);

        room_manager.add_room("main_menu", &main_menu_room);
        room_manager.add_room("game", &game_room);
        room_manager.add_room("upgrade", &upgrade_room);
        room_manager.change_room("main_menu");

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

        room_manager.close();
    } catch (const std::exception &e) {
        std::cerr << "ERRO CRITICO: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}