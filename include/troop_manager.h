#ifndef TROOP_MANAGER_H
#define TROOP_MANAGER_H

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <memory>
#include "room.h"
#include "troop_card.h"
#include "troop.h"
#include "field_troop.h"
#include "globals.h"
#include "troop_projectile.h"

class GameRoom;

class TroopManager {
private:
    GameRoom &_room;
    std::array<TroopCard *, TROOP_COUNT> _shop_cards;
    std::array<Troop *, (TROOP_ROWS * TROOP_COLS)> _troops;
    std::vector<FieldTroop *> _field_troops;
    std::vector<std::unique_ptr<TroopProjectile>> _projectiles;
    TroopType _cursor_troop = TroopType::None; // tropa selecionada no mouse
    sf::Rect<float> _enemy_area;               // retangulo da area dos inimigos

private:
    /// Retorna -1 se a posicao nao esta em nenhum slot, ou o numero do slot se estiver
    int position_to_slot(sf::Vector2f position);

    sf::RenderWindow &get_window();

    /// Retorna a posicao do mouse com o y fixado na linha mais proxima
    sf::Vector2f get_line_pos();

    /// Desenha os slots das tropas no canto esquerdo
    void draw_slots();

    /// Desenha as cartas da loja no canto direito
    void draw_shop();

    /// Coloca uma tropa no slot do mouse (se tiver em um slot)
    void place_troop();

    /// Instancia o objeto Troop do tipo informado (nao aceita field_troop)
    /// E nao insere no array
    Troop *instantiate_troop(int slot, TroopType troop_type);

    /// Instancia o objeto FieldTroop do tipo informado (nao insere no vetor)
    FieldTroop *instantiate_field_troop(sf::Vector2f position, TroopType troop_type);

public:
    TroopManager(GameRoom &room);

    ~TroopManager();

    void run(double dt, const std::vector<sf::Event> &event_queue);

    void draw();

    void spawn_projectile(std::unique_ptr<TroopProjectile> projectile);

    std::array<TroopType, TROOP_ROWS * TROOP_COLS> get_troops();
    void set_troops(std::array<TroopType, TROOP_ROWS * TROOP_COLS> troops);

    const std::vector<FieldTroop *> &get_field_troops();
    void set_field_troops(const std::vector<std::pair<TroopType, sf::Vector2f>> &field_troops);

    FieldTroop *get_field_troop_at(sf::Vector2f position);
};

#endif