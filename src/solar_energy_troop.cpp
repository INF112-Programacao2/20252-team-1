#include "solar_energy_troop.h"
#include "game_manager.h"
#include <random>
#include <sstream>

sf::Texture SolarEnergyTroop::_texture;

SolarEnergyTroop::SolarEnergyTroop(sf::Vector2f position, int line, double cooldown,
                                   int increase_points, Room &room)
    : Troop(position, line, cooldown, room), _points_text(position, 1, room) {

    _type = TroopType::SolarEnergy;
    sf::Text text("", GameManager::get_instance().get_font(), 30);
    _points_text.set_text(text);
    _increase_points = increase_points;
}

bool SolarEnergyTroop::fire() {
    // spawna texto informando quantos pontos gerou
    std::stringstream s;
    s << "+" << _increase_points * GameManager::get_instance().get_point_multiplier();

    _points_text.set_string(s.str());
    float rand_x = (std::rand() / (float)RAND_MAX) * 40 - 20;
    _points_text.set_position(_position + sf::Vector2f(rand_x, 0));
    _points_text.restart();

    // aumenta a score
    GameManager::get_instance().add_points(_increase_points);
    return true;
}

void SolarEnergyTroop::run(double dt) {
    Troop::run(dt);

    _points_text.run(dt);
}

void SolarEnergyTroop::draw() {
    sf::RectangleShape sprite(sf::Vector2f(100, 100));
    sprite.setPosition(_position);
    sprite.setTexture(&_texture);

    _room.get_window().draw(sprite);
    _points_text.draw();
}

sf::Texture &SolarEnergyTroop::get_texture() {
    return _texture;
}

bool SolarEnergyTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}