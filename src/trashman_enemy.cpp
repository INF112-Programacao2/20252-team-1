#include "trashman_enemy.h"
#include "trash_enemy.h" //precisa conhecer o TrashEnemy para spawnar
#include "game_room.h"

sf::Texture TrashmanEnemy::_texture;

//altura visual
const float height = 150;
//distancia que ele para do muro (maior que a do Hunter que eh 400)
const float SPAWN_RANGE = 600.0f;

TrashmanEnemy::TrashmanEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room)
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room) {

    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setSize({width, height});
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    _shape.setPosition(get_position());
}

bool TrashmanEnemy::can_walk(double next_position) {
    // para de andar antes do hunter (anda menos) ficando mais longe do muro
    return next_position > (WALL_POSITION_X + WALL_WIDTH + SPAWN_RANGE);
}

void TrashmanEnemy::attack() {
    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    // cria o inimigo Lixo na posicao atual do Lixeiro
    auto trash = std::make_shared<TrashEnemy>(
        40,          // vida do lixo
        _damage,     // dano (usa o dano base do lixeiro)
        _line,       // mesma linha
        350.0,       // velocidade (rapido pq ele rola)
        0.0,         // cooldown (nao ataca so explode)
        0,           // pontos ao destruir o lixo
        _position_x, // posicao x inicial (onde o lixeiro esta)
        _room        // sala
    );

    // adiciona o lixo na WaveManager para ele se comportar como um inimigo normal
    // talvez tenha um jeito melhor de fazer isso
    game_room.get_wave_manager().add_enemy(trash);
}

void TrashmanEnemy::run(double dt) {
    Enemy::run(dt);
}

void TrashmanEnemy::draw() {
    _shape.setTexture(&_texture);
    Enemy::draw();
}

bool TrashmanEnemy::load_texture(const std::string &file_path) {
    return _texture.loadFromFile(file_path);
}