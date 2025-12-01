#include "fire_enemy.h"
#include "game_room.h"
#include "game_manager.h" //tem que incluir para pontos

sf::Texture FireEnemy::_texture;

const float height = 100;

FireEnemy::FireEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, double burn_duration, Room &room)
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room), _burn_duration(burn_duration) {

    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    _shape.setSize({width, height});
}

bool FireEnemy::can_walk(double next_position) {
    // mantem a logica padrao, para no muro
    return next_position > WALL_POSITION_X + WALL_WIDTH;
}

void FireEnemy::run(double dt) {
    Enemy::run(dt);
}

void FireEnemy::draw() {
    _shape.setTexture(&_texture);
    Enemy::draw();
}

void FireEnemy::attack(FieldTroop* field_troop) {
    if (field_troop) {
        field_troop->hit(_damage); // nao da efeito de fogo

        _health.set_life(0);
        return;
    }

    GameRoom &game_room = dynamic_cast<GameRoom &>(_room);

    // muro pegando fogo bicho
    // ajustar conforme necessario
    game_room.get_wall().start_burning(_burn_duration, _damage);

    // inimigo kamikaze
    // seta a vida pra 0 para triggar o callback de morte (que da os pontos) (talvez n dar pontos?)
    _health.set_life(0);
}

bool FireEnemy::load_texture(const std::string &file_path) {
    return _texture.loadFromFile(file_path);
}

double FireEnemy::get_type_multiplier(ProjectileType type) {
    switch (type) {
    case ProjectileType::ElephantProjectileType:
        return 5.0; // critico
    case ProjectileType::DolphinProjectileType:
        return 2.0;

    default:
        return 0.25;
    }
}