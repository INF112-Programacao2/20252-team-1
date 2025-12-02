#ifndef CREDITS_ROOM_H
#define CREDITS_ROOM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "room.h"

class CreditsRoom : public Room {
private:
    sf::Font _font;

    sf::Texture _title_texture;
    sf::Sprite _title_sprite;

    sf::Texture _background_texture;
    sf::Sprite _background_sprite;

    sf::Text _credits_text;
    sf::Text _names_text;

    // para o botao de voltar no topo esquerdo
    sf::Texture _arrow_texture;
    sf::Sprite _arrow_sprite;

public:
    CreditsRoom(sf::RenderWindow& window, RoomManager& room_manager);

    ~CreditsRoom() = default;

    void change_room(std::string room_name);

    void start();

    void run(double dt, const std::vector<sf::Event>& event_queue);

    void draw();

    void end() {};
};

#endif