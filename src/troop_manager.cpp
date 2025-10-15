#include <iostream>
#include "troop_manager.h"
#include "solar_energy_troop.h"
#include "hedgehog_troop.h"

const sf::Vector2f offset(50, 100); // posicao inicial dos slots (superior esquerdo)
const float gap_x = 175; // distancia horizontal dos slots
const float gap_y = 200; // distancia vertical dos slots

const float troop_radius = 75; // raio do slot

TroopManager::TroopManager(Room &room) : _room(room) {
    // inicializando array de tropas vazio
    for (size_t i = 0; i < _troops.size(); i++)
        _troops[i] = nullptr;

    // atualizando tamanho da area dos inimigos
    sf::Vector2f start(WALL_POSITION_X + WALL_WIDTH + 50, 100);
    _enemy_area = sf::Rect(start, sf::Vector2f(GAME_SIZE_X - 50, DESKTOP_SIZE.y - 100) - start);

    // criando array de cartas (itens da loja)
    const int item_width = 125;

    float size_x = get_window().getView().getSize().x;
    int shop_width = size_x - GAME_SIZE_X;

    const int cols = 2;
    float gap = (shop_width - item_width * cols) / (float)(cols + 1);

    int idx = 0;
    for (int i = 0; i <= TROOP_COUNT / cols; i++) {
        for (int j = 0; j < cols && idx < TROOP_COUNT; j++, idx++) {
            _shop_cards[idx] = new TroopCard(
                sf::Vector2f(
                    size_x - shop_width + (gap * (j + 1) + item_width * j),
                    75 + 200 * i),
                item_width, (TroopType)idx, TROOP_PRICES[idx], _room);
        }
    }
}

TroopManager::~TroopManager() {
    for (TroopCard *card : _shop_cards)
        delete card;

    for (Troop *troop : _troops)
        delete troop;

    for (FieldTroop *troop : _field_troops)
        delete troop;
};

sf::RenderWindow &TroopManager::get_window() {
    return _room.get_window();
}

int TroopManager::position_to_slot(sf::Vector2f position) {
    for (int i = 0; i < TROOP_ROWS; i++) {
        for (int j = 0; j < TROOP_COLS; j++) {
            float dx = position.x - troop_radius - (offset.x + gap_x * j);
            float dy = position.y - troop_radius - (offset.y + gap_y * i);
            if (dx * dx + dy * dy < troop_radius * troop_radius)
                return i * TROOP_COLS + j;
        }
    }

    return -1;
}

void TroopManager::draw_slots() {
    sf::CircleShape slot_ui = sf::CircleShape(troop_radius);
    slot_ui.setFillColor(sf::Color(255, 255, 255, 100));

    for (int i = 0; i < TROOP_ROWS; i++) {
        for (int j = 0; j < TROOP_COLS; j++) {
            slot_ui.setPosition(
                sf::Vector2f(offset.x + gap_x * j, offset.y + gap_y * i));

            // efeito hover
            int slot_idx = i * TROOP_COLS + j;
            if (position_to_slot((sf::Vector2f)_room.get_mouse_position()) == slot_idx)
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

void TroopManager::draw() {
    draw_slots();
    draw_shop();

    for (Troop *troop : _troops) {
        if (troop)
            troop->draw();
    }

    for (FieldTroop *field_troop : _field_troops) {
        if (field_troop)
            field_troop->draw();
    }
}

void TroopManager::place_troop() {
    sf::Vector2f mouse_pos = (sf::Vector2f)_room.get_mouse_position();

    // TODO: adicionar as outras tropas que sao do tipo FieldTroop
    if (_cursor_troop == TroopType::Hedgehog) {
        if (_enemy_area.contains(mouse_pos)) {
            FieldTroop *field_troop;

            switch (_cursor_troop) {
                case TroopType::Hedgehog:
                    field_troop = new HedgehogTroop(mouse_pos, 30.0, 2, _room);
                    break;

                default:
                    std::cerr << "Tropa nao adicionada!" << std::endl;
                    break;
            }

            _field_troops.push_back(field_troop);
            _cursor_troop = TroopType::None;
        }

        return;
    }

    int slot = position_to_slot(mouse_pos);
    if (slot != -1 && _troops[slot] == nullptr && _cursor_troop != TroopType::None) {
        int row = slot / TROOP_COLS;
        int col = slot % TROOP_COLS;
        sf::Vector2f position(
            25 + offset.x + gap_x * col,
            25 + offset.y + gap_y * row);

        // TODO: escolher a classe certa pra cada tipo de tropa
        Troop *troop;
        switch (_cursor_troop) {
            case TroopType::SolarEnergy:
                troop = new SolarEnergyTroop(position, 5.0, 100, _room);
                break;

            //! DEBUG (Troop deveria ser uma interface)
            default:
                troop = new Troop(position, 5.0, _room);
                break;
        }

        _troops[slot] = troop;
        _cursor_troop = TroopType::None;

        return;
    }

    if (_cursor_troop == TroopType::None) {
        for (TroopCard *card : _shop_cards) {
            if (card->position_meeting(mouse_pos))
            _cursor_troop = card->buy();
        }
    }
}

void TroopManager::run(double dt, const std::vector<sf::Event> &event_queue) {
    for (Troop *troop : _troops) {
        if (troop != nullptr)
            troop->run(dt);
    }

    for (int i = 0; i < _field_troops.size(); i++) {
        FieldTroop *field_troop = _field_troops[i];

        if (!field_troop)
            _field_troops.erase(_field_troops.begin() + i--); // tira do vetor e volta o i
        else if (field_troop->is_dead()) {
            delete field_troop;
            _field_troops.erase(_field_troops.begin() + i--); // tira do vetor e volta o i
        } else
            field_troop->run(dt);
    }

    // colocando uma tropa no mapa
    for (const sf::Event &event : event_queue) {
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left)
                place_troop();
            else if (event.mouseButton.button == sf::Mouse::Right) {
                // remove a tropa do slot que o mouse esta (se estiver em um)
                int slot = position_to_slot((sf::Vector2f)_room.get_mouse_position());
                if (slot != -1 && _troops[slot] != nullptr) {
                    delete _troops[slot];
                    _troops[slot] = nullptr;
                }
            }
        }
    }
}

void TroopManager::pause() {
    for (Troop* troop : _troops) {
        if (troop != nullptr)
            troop->reset_timer();
    }
}