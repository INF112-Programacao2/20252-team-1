#include "troop_manager.h"
#include "solar_energy_troop.h"
#include "hedgehog_troop.h"
#include "monkey_troop.h"
#include "game_manager.h"
#include "game_room.h"
#include "globals.h"
#include <iostream>

// posicao inicial dos slots (superior esquerdo)
const sf::Vector2f offset(50, HUD_HEIGHT + PADDING_Y);
const float gap_x = 175; // distancia horizontal dos slots

// helper
sf::Texture *get_troop_texture(TroopType troop) {
    switch (troop) {
    case TroopType::Hedgehog:
        return &HedgehogTroop::get_texture();

    case TroopType::SolarEnergy:
        return &SolarEnergyTroop::get_texture();

    case TroopType::Monkey:
        return &MonkeyTroop::get_texture();

    default:
        return nullptr;
    }
}

TroopManager::TroopManager(GameRoom &room) : _room(room) {
    // inicializando texturas das tropas:
    if (!HedgehogTroop::load_texture("assets/ourico.png")) {
        std::cerr << "Nao achou o asset do ourico!\n";
        std::exit(1);
    }

    if (!SolarEnergyTroop::load_texture("assets/energia solar.png")) {
        std::cerr << "Nao achou o asset energia solar!\n";
        std::exit(1);
    }

    if (!MonkeyTroop::load_texture("assets/monkey.png")) {
        std::cerr << "Nao achou o asset monkey!\n";
        std::exit(1);
    }

    // inicializando array de tropas vazio
    for (size_t i = 0; i < _troops.size(); i++)
        _troops[i] = nullptr;

    // atualizando tamanho da area dos inimigos
    sf::Vector2f start(WALL_POSITION_X + WALL_WIDTH + 50, HUD_HEIGHT);
    _enemy_area = sf::Rect<float>( // G: N compilava nem fudendo sem esse <float>
      start, sf::Vector2f(GAME_SIZE_X - 50, DESKTOP_SIZE.y) - start);

    // criando array de cartas (itens da loja)
    const int item_width = 125;

    float size_x = get_window().getView().getSize().x;
    int shop_width = size_x - GAME_SIZE_X;

    const int cols = 2;
    float gap = (shop_width - item_width * cols) / (float)(cols + 1);

    int idx = 0;
    for (int i = 0; i <= TROOP_COUNT / cols; i++) {
        for (int j = 0; j < cols && idx < TROOP_COUNT; j++, idx++) {
            sf::Vector2f position(
                size_x - shop_width + (gap * (j + 1) + item_width * j),
                75 + 200 * i);

            _shop_cards[idx] = new TroopCard(
                position, item_width, (TroopType)idx, TROOP_PRICES[idx],
                get_troop_texture((TroopType)idx), _room);
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
            float dx = position.x - TROOP_RADIUS - (offset.x + gap_x * j);
            float dy = position.y - TROOP_RADIUS - (offset.y + GAP_Y * i);
            if (dx * dx + dy * dy < TROOP_RADIUS * TROOP_RADIUS)
                return i * TROOP_COLS + j;
        }
    }

    return -1;
}

void TroopManager::draw_slots() {
    sf::CircleShape slot_ui = sf::CircleShape(TROOP_RADIUS);
    slot_ui.setFillColor(sf::Color(255, 255, 255, 100));

    for (int i = 0; i < TROOP_ROWS; i++) {
        for (int j = 0; j < TROOP_COLS; j++) {
            slot_ui.setPosition(
                sf::Vector2f(offset.x + gap_x * j, offset.y + GAP_Y * i));

            // efeito hover
            int slot_idx = i * TROOP_COLS + j;
            if (!_room.is_paused() &&
                position_to_slot((sf::Vector2f)_room.get_mouse_position()) == slot_idx) {

                slot_ui.setFillColor(sf::Color(255, 255, 255, 200));
            } else
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

sf::Vector2f TroopManager::get_line_pos() {
    return GameManager::get_line_pos((sf::Vector2f)_room.get_mouse_position());
}

void TroopManager::draw() {
    draw_slots();

    // desenha tropas
    for (Troop *troop : _troops) {
        if (troop)
            troop->draw();
    }

    // desenha tropas de campo
    for (FieldTroop *field_troop : _field_troops) {
        if (field_troop)
            field_troop->draw();
    }

    // desenha projeteis
    for (auto &projectile : _projectiles)
        projectile->draw();

    draw_shop();

    // desenha tropa no cursor
    if (_cursor_troop == TroopType::None || _room.is_paused())
        return;

    bool is_fieldtroop = (_cursor_troop == TroopType::Hedgehog);

    sf::Vector2f mouse_pos = (sf::Vector2f)_room.get_mouse_position();
    sf::Texture *texture = get_troop_texture(_cursor_troop);

    if (texture) {
        sf::RectangleShape sprite(sf::Vector2f(60, 60));
        sf::Vector2f position = is_fieldtroop ? get_line_pos() : mouse_pos;
        sprite.setPosition(position - sf::Vector2f(30, 30));
        sprite.setTexture(texture);

        if (is_fieldtroop && !_enemy_area.contains(get_line_pos()))
            sprite.setFillColor(sf::Color(255, 0, 0, 150));
        else
            sprite.setFillColor(sf::Color(255, 255, 255, 150));

        get_window().draw(sprite);
    } else {
        sf::CircleShape circle(30);
        circle.setPosition(mouse_pos - sf::Vector2f(30, 30));
        circle.setFillColor(sf::Color(255, 0, 0, 100));

        get_window().draw(circle);
    }
}

Troop* TroopManager::instantiate_troop(int slot, TroopType troop_type) {
    if (slot == -1 || _troops[slot] != nullptr || troop_type == TroopType::None)
        return nullptr;

    int row = slot / TROOP_COLS;
    int col = slot % TROOP_COLS;

    int line = row + 1;
    sf::Vector2f position(25 + offset.x + gap_x * col, 25 + offset.y + GAP_Y * row);

    // TODO: colocar o resto dos tipos de tropas
    switch (troop_type) {
    case TroopType::SolarEnergy:
        return new SolarEnergyTroop(position, line, 5.0, 100, _room);

    //! DEBUG (Troop deveria ser uma interface)
    default:
        return new Troop(position, line, 5.0, _room);
    }
}

FieldTroop* TroopManager::instantiate_field_troop(sf::Vector2f position, TroopType troop_type) {
    if (!_enemy_area.contains(position))
        return nullptr;

    // TODO: adicionar as outras tropas que sao do tipo FieldTroop
    switch (troop_type) {
    case TroopType::Hedgehog:
        return new HedgehogTroop(position, 75.0, 0.5, _room);

    default:
        std::cout << troop_type << std::endl; //!DEBUG
        std::cerr << "FieldTroop nao adicionada!" << std::endl;
        return nullptr;
    }
}

void TroopManager::place_troop() {
    sf::Vector2f mouse_pos = (sf::Vector2f)_room.get_mouse_position();

    if (FieldTroop* field_troop = instantiate_field_troop(get_line_pos(), _cursor_troop)) {
        _field_troops.push_back(field_troop);
        _cursor_troop = TroopType::None;

        return;
    }

    int slot = position_to_slot(mouse_pos);
    if (Troop* troop = instantiate_troop(slot, _cursor_troop)) {
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

    // Run dos projeteis das troops
    for (int i = 0; i < _projectiles.size(); ) {
        _projectiles[i]->run(dt);

        if (_projectiles[i]->is_destroyed()) {
            std::swap(_projectiles[i], _projectiles.back());
            _projectiles.pop_back();
        } else
            i++;
    }

    // Run do field troop
    for (int i = 0; i < _field_troops.size(); ) {
        FieldTroop *field_troop = _field_troops[i];

        if (!field_troop || field_troop->is_destroyed()) {
            delete field_troop;
            std::swap(_field_troops[i], _field_troops.back());
            _field_troops.pop_back();
        } else {
            field_troop->run(dt);
            i++;
        }
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
                } else if (_cursor_troop != TroopType::None) {
                    // cancela a compra e reembolsa
                    // (se o mouse estiver fora de um slot ocupado)
                    GameManager::get_instance().add_points(TROOP_PRICES[_cursor_troop]);
                    _cursor_troop = TroopType::None;
                }
            }
        }
    }
}

void TroopManager::spawn_projectile(std::unique_ptr<TroopProjectile> projectile) {
    _projectiles.push_back(std::move(projectile));
}

std::array<TroopType, TROOP_ROWS * TROOP_COLS> TroopManager::get_troops() {
    std::array<TroopType, TROOP_ROWS * TROOP_COLS> result;
    for (int i = 0; i < _troops.size(); i++)
        result[i] = (_troops[i] == nullptr) ? TroopType::None : _troops[i]->get_type();

    return result;
}

void TroopManager::set_troops(std::array<TroopType, TROOP_ROWS * TROOP_COLS> troops) {
    for (int slot = 0; slot < troops.size(); slot++) {
        delete _troops[slot];
        _troops[slot] = instantiate_troop(slot, troops[slot]);
    }
}

const std::vector<FieldTroop *> &TroopManager::get_field_troops() {
    return _field_troops;
}

void TroopManager::set_field_troops(const std::vector<std::pair<TroopType, sf::Vector2f>> &field_troops) {
    for (FieldTroop* field_troop : _field_troops)
        delete field_troop;

    _field_troops.clear();
    _field_troops.reserve(field_troops.size());
    for (auto [troop_type, position] : field_troops) {
        _field_troops.push_back(instantiate_field_troop(position, troop_type));
    }
}