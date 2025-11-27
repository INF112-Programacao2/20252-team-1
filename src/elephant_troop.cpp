#include "elephant_troop.h"
#include "game_manager.h"
#include "game_room.h"
#include "troop_manager.h"

sf::Texture ElephantTroop::_texture;

ElephantTroop::ElephantTroop(sf::Vector2f position, int line, double cooldown, Room& room)
    : Troop(position, line, cooldown, room) {
    _type = TroopType::Elephant;
}

void ElephantTroop::run(double dt) {
    Troop::run(dt);
}

void ElephantTroop::draw() {
    sf::RectangleShape sprite(sf::Vector2f(100, 100));
    sprite.setPosition(_position);
    sprite.setTexture(&_texture);
    _room.get_window().draw(sprite);
}

void ElephantTroop::fire() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    //loop de todas as lanes -> REDO?: isso eh mt ruim!!!!!
    for (int line = 1; line <= 4; line++) {
        std::shared_ptr<Enemy> target = game_room.get_wave_manager().get_closest_enemy_on_line(line);

        //so atira se tiver alvo na lane
        if (target) {
            int damage = 15;
            double speed = 350.0;
            double fire_reduce = 1.0; //reduz 1 segundo de fogo

            auto projectile = std::make_unique<ElephantProjectile>(
                _position + sf::Vector2f(50, 50),
                target,
                damage,
                speed,
                fire_reduce,
                _room);

            game_room.get_troop_manager().spawn_projectile(std::move(projectile));
        }
    }
}

sf::Texture& ElephantTroop::get_texture() {
    return _texture;
}

bool ElephantTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}