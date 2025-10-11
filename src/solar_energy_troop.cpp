#include "solar_energy_troop.h"
#include "game_manager.h"

SolarEnergyTroop::SolarEnergyTroop(sf::Vector2f position, double cooldown, int increase_points, Room &room)
    : Troop(position, cooldown, room) {
    _increase_points = increase_points;
}

void SolarEnergyTroop::fire() {
    GameManager::get_instance().add_points(_increase_points);
}

void SolarEnergyTroop::draw() {
    sf::CircleShape circle(50.0);
    circle.setPosition(_position);
    circle.setFillColor(sf::Color::Yellow);

    _room.get_window().draw(circle);
}