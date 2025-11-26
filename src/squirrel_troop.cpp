#include "squirrel_troop.h"
#include "squirrel_projectile.h"
#include "game_room.h"
#include "game_manager.h"
#include "wave_manager.h"
#include "troop_manager.h"

sf::Texture SquirrelTroop::_texture;

SquirrelTroop::SquirrelTroop(sf::Vector2f position, int line, double cooldown, Room& room)
    : Troop(position, line, cooldown, room) {
    _type = TroopType::Squirrel;
}

void SquirrelTroop::run(double dt) {
    Troop::run(dt);
}

void SquirrelTroop::draw() {
    sf::RectangleShape sprite(sf::Vector2f(100, 100));
    sprite.setPosition(_position);
    sprite.setTexture(&_texture);
    _room.get_window().draw(sprite);
}

void SquirrelTroop::fire() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    //encontra o alvo (inimigo mais proximo na linha)
    std::shared_ptr<Enemy> target = game_room.get_wave_manager().get_closest_enemy_on_line(_line);

    if (target) {
        int damage = 40;        //dano base da noz
        double speed = 400.0;   //velocidade do projetil
        double radius = 150.0;  //raio da explosao -> aumentar com upgrades

        //cria o projetil com ponteiro para o alvo e raio de explosao
        auto projectile = std::make_unique<SquirrelProjectile>(
            _position + sf::Vector2f(50, 50), //spawna no meio da tropa
            target,
            damage,
            speed,
            radius,
            _room);
        //adiciona ao gerenciador
        game_room.get_troop_manager().spawn_projectile(std::move(projectile));
    }
}

sf::Texture &SquirrelTroop::get_texture() {
    return _texture;
}

bool SquirrelTroop::load_texture(std::string file_path) {
    return _texture.loadFromFile(file_path);
}