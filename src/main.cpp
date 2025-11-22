#include <SFML/Graphics.hpp>
#include <iostream>
#include "room_manager.h"
#include "game_room.h"
#include "game_manager.h"
#include "main_menu_room.h"
#include "upgrade_room.h"
#include "game_saver.h"

int main() {
    std::srand(std::time(0));

    // carrega a fonte no game manager
    if (!GameManager::get_instance().load_font("assets/Minecraftia-Regular.ttf")) {
        std::cerr << "***\nNao foi possivel encontrar a fonte em \""
                  << "assets/Minecraftia-Regular.ttf"
                  << "\"\n***" << std::endl;

        std::exit(1);
    }

    const bool FULLSCREEN = true; //! Use false somente para debug
    const bool WINDOWS = false;   //! DEBUG, coloque true se esta compilando para windows

    // TODO: CONCERTAR A RESOLUCAO DA TELA (NAO FUNCIONA EM TODO PC)

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

    window.setVerticalSyncEnabled(false);

    // Carregando informacoes do jogo
    GameSaver game_saver("save.txt");
    game_saver.load();

    // Criando as salas
    RoomManager room_manager;

    GameRoom game_room(window, room_manager, game_saver.get_wall_life(), 0);
    MainMenuRoom main_menu_room(window, room_manager);
    UpgradeRoom upgrade_room(window, room_manager);

    room_manager.add_room("main_menu", &main_menu_room);
    room_manager.add_room("game", &game_room);
    room_manager.add_room("upgrade", &upgrade_room);
    room_manager.change_room("game");

    // Restaurando estado anterior
    GameManager::get_instance().add_points(game_saver.get_points());
    game_room.get_wave_manager().set_wave_idx(game_saver.get_wave_idx());
    game_room.get_troop_manager().set_troops(game_saver.get_troops());
    game_room.get_troop_manager().set_field_troops(game_saver.get_field_troops());

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

            // Vai pra room de upgrades quando se aperta 'U'
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::U) {
                room_manager.change_room("upgrade");
            }

            // Vai pra room do jogo quando se aperta 'G'
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::G) {
                room_manager.change_room("game");
            }

            room_manager.add_event(event);
        }

        room_manager.run(delta_clock.restart().asSeconds());
    }

    //! DEBUG (so deve salvar no inicio de uma wave)
    game_saver.set_wave_idx(game_room.get_wave_manager().get_wave_idx());
    game_saver.set_points(GameManager::get_instance().get_points());
    game_saver.set_wall_life(game_room.get_wall().get_life());
    game_saver.set_troops(game_room.get_troop_manager().get_troops());
    game_saver.set_field_troops(game_room.get_troop_manager().get_field_troops());

    game_saver.save();

    return 0;
}