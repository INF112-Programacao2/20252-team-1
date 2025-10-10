#include "game_room.h"

GameRoom::GameRoom(sf::RenderWindow &window)
    : Room(window), _troop_manager(*this) {}

GameRoom::~GameRoom() = default;

void GameRoom::start() {}

void GameRoom::run(double dt, const std::vector<sf::Event> &event_queue) {
    _troop_manager.run(dt, event_queue);

    _window.clear(sf::Color(50, 150, 50));

    _troop_manager.draw();

    _window.display();
}

void GameRoom::end() {}