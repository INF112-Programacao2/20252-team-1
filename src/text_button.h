#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "room.h"

class TextButton {
private:
    sf::Text _draw_text;
    sf::Vector2f _position;
    std::function<void()> _on_click_callback; // funcao pra chamar quando for clicado
    Room &_room;

public:
    TextButton(std::string text, sf::Font &font, int font_size, Room &room);
    TextButton(std::string text, sf::Font &font, int font_size,
               std::function<void()> on_click_callback, Room &room);

    sf::Vector2f get_position();

    void set_position(sf::Vector2f position);

    /// Adiciona offset na posicao atual
    void offset_position(sf::Vector2f offset);

    /// Centraliza no meio da tela o texto
    void center();

    /// Roda todo frame pra checar se o botao foi pressionado
    void run(const std::vector<sf::Event> &event_queue);

    void draw();

    /// Checa se uma posicao esta dentro do texto (geralmente a do mouse)
    bool position_meeting(sf::Vector2i position);
};

#endif