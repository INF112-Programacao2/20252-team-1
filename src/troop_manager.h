#ifndef TROOP_MANAGER_H
#define TROOP_MANAGER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "room.h"
#include "troop_card.h"
#include "troop.h"
#include "field_troop.h"
#include "globals.h"

class TroopManager {
private:
    Room &_room;
    std::array<TroopCard *, TROOP_COUNT> _shop_cards;
    std::array<Troop *, (TROOP_ROWS * TROOP_COLS)> _troops;
    std::vector<FieldTroop *> _field_troops;
    TroopType _cursor_troop = TroopType::None; // tropa selecionada no mouse
    sf::Rect<float> _enemy_area; // retangulo da area dos inimigos

private:
    /// Retorna -1 se a posicao nao esta em nenhum slot, ou o numero do slot se estiver
    int position_to_slot(sf::Vector2f position);

    sf::RenderWindow &get_window();

    /// Desenha os slots das tropas no canto esquerdo
    void draw_slots();

    /// Desenha as cartas da loja no canto direito
    void draw_shop();

    /// Coloca uma tropa no slot do mouse (se tiver em um slot)
    void place_troop();

public:
    TroopManager(Room &room);

    ~TroopManager();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void draw();

    /// Logica de pause, pausa o timer das tropas (chamado todo frame enquanto pausado)
    void pause();
};

#endif