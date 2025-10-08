#include <iostream> //! DEBUG
#include "troop_manager.h"

const sf::Vector2f offset(50, 100);
const float gap_x = 175;
const float gap_y = 200;

const float troop_radius = 75;

const int rows = 4;
const int cols = 3;

TroopManager::TroopManager(Room &room) : _room(room) {
    // criando array de cartas (itens da loja)
    const int cols = 2;
    const int item_width = 125;

    float size_x = get_window().getView().getSize().x;
    int shop_width = size_x - GAME_SIZE_X;

    float gap = (shop_width - item_width * cols) / (float)(cols + 1);

    int idx = 0;
    for (int i = 0; i <= TROOP_COUNT / cols; i++) {
        for (int j = 0; j < cols && idx < TROOP_COUNT; j++, idx++) {
            _shop_cards[idx] = new TroopCard(
                sf::Vector2f(
                    size_x - shop_width + (gap * (j + 1) + item_width * j),
                    75 + 200 * i),
                item_width, (TroopType)idx, _room);
        }
    }
}

TroopManager::~TroopManager() {
    for (auto card : _shop_cards)
        delete card;
};

sf::RenderWindow &TroopManager::get_window() {
    return _room.get_window();
}

/// Retorna -1 se a posicao nao esta em nenhum slot, ou o numero do slot se
/// estiver
int TroopManager::position_to_slot(sf::Vector2f position) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float dx = position.x - troop_radius - (offset.x + gap_x * j);
            float dy = position.y - troop_radius - (offset.y + gap_y * i);
            if (dx * dx + dy * dy < troop_radius * troop_radius)
                return i * cols + j;
        }
    }

    return -1;
}

sf::Vector2f TroopManager::get_mouse_pos() {
    return sf::Vector2f(
        sf::Mouse::getPosition(get_window()).x,
        sf::Mouse::getPosition(get_window()).y);
}

/// Desenha os slots das tropas no canto esquerdo
void TroopManager::draw_slots() {
    sf::CircleShape slot_ui = sf::CircleShape(troop_radius);
    slot_ui.setFillColor(sf::Color(255, 255, 255, 100));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            slot_ui.setPosition(
                sf::Vector2f(offset.x + gap_x * j, offset.y + gap_y * i));

            // efeito hover
            int slot_idx = i * cols + j;
            if (position_to_slot(get_mouse_pos()) == slot_idx)
                slot_ui.setFillColor(sf::Color(255, 255, 255, 200));
            else
                slot_ui.setFillColor(sf::Color(255, 255, 255, 100));

            get_window().draw(slot_ui);
        }
    }
}

void TroopManager::draw_shop() {
    float size_x = get_window().getView().getSize().x;
    float size_y = get_window().getView().getSize().y;

    // desenha fundo
    int shop_width = size_x - GAME_SIZE_X;
    sf::RectangleShape background(sf::Vector2f(shop_width, size_y));
    background.setPosition(sf::Vector2f(size_x - shop_width, 0));
    background.setFillColor(sf::Color(150, 150, 50));

    get_window().draw(background);

    // desenha cartas da loja
    for (TroopCard *card : _shop_cards)
        card->draw();
}

void TroopManager::run(double _dt, const std::vector<sf::Event> &event_queue) {
    for (const sf::Event &event : event_queue) {
        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left) {
            for (TroopCard *card : _shop_cards) {
                if (card->position_meeting(get_mouse_pos()))
                    std::cout << card->get_troop() << std::endl;
            }
        }
    }
}