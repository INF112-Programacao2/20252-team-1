#include "solar_energy_troop.h"
#include "game_manager.h"

sf::Texture SolarEnergyTroop::_texture;

SolarEnergyTroop::SolarEnergyTroop(sf::Vector2f position, double cooldown, int increase_points, Room &room)
    : Troop(position, cooldown, room) {
    _increase_points = increase_points;
}

void SolarEnergyTroop::fire() {
    GameManager::get_instance().add_points(_increase_points);
}

void SolarEnergyTroop::draw() {
    sf::RectangleShape sprite(sf::Vector2f(100, 100));
    sprite.setPosition(_position);
    sprite.setTexture(&_texture);

    _room.get_window().draw(sprite);
}

sf::Texture &SolarEnergyTroop::get_texture() {
    return _texture;
}

bool SolarEnergyTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}