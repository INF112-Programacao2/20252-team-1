#include "wall.h"
#include "room_manager.h"
#include "globals.h"
#include <iostream> //! DEBUG

Wall::Wall(int base_life, int spike_damage, Room &room)
    : _health(base_life, std::bind(&Wall::destroy, this)), _spike_damage(spike_damage), _room(room) {
    _collider = sf::Rect<float>(
        sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT),
        sf::Vector2f(WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT));
};

Wall::~Wall() = default;

void Wall::destroy() {
    // Callback chamado quando a vida do muro chega a zero -> ondeathcallback
    // a ideia eh ter algo de verdade aqui -> discutir c/ grupo
    std::cout << "O muro foi de arrasta pra cima" << std::endl;
}

bool Wall::collide(sf::Vector2f position) {
    return _collider.contains(position);
}

void Wall::draw() {
    sf::RectangleShape wall_shape(sf::Vector2f(WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT));
    wall_shape.setPosition(sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT));
    wall_shape.setFillColor(sf::Color(128, 128, 128)); // cor cinza para o muro

    _room.get_window().draw(wall_shape);
}