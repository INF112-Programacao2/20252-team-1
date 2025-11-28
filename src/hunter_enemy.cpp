#include "hunter_enemy.h"
#include "game_room.h"
#include "globals.h"

sf::Texture HunterEnemy::_texture;
sf::Texture HunterEnemy::_projectile_texture;

// Altura visual
const float height = 100;
// Distancia do muro que ele deve parar
const float ATTACK_RANGE = 400.0f; 

HunterEnemy::HunterEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, Room &room)
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room) {

    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setSize({width, height});
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    _shape.setPosition(get_position());

}

bool HunterEnemy::can_walk(double next_position) {
    // Para de andar se proxima posição for menor ou igual que a posicao + largura do muro + alcance
    return next_position > (WALL_POSITION_X + WALL_WIDTH + ATTACK_RANGE);
}

void HunterEnemy::run(double dt) {
    Enemy::run(dt);
}

void HunterEnemy::draw() {
    _shape.setTexture(&_texture);
    Enemy::draw();
}

void HunterEnemy::attack() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    // Projetil central
    auto proj_meio = std::make_unique<EnemyProjectile>(
        get_position(), 
        shared_from_this(), 
        game_room.get_wall(), 
        _damage, 
        260.0,  // Velocidade do projetil
        _room
    );
    proj_meio->set_texture(&_projectile_texture);
    game_room.get_wave_manager().spawn_projectile(std::move(proj_meio));

    // Projetil de cima
    auto proj_cima = std::make_unique<EnemyProjectile>(
        get_position() + sf::Vector2f(0, -25), // Altera o y para ele ficar em cima do projetil central
        shared_from_this(), 
        game_room.get_wall(), 
        _damage, 
        250.0, 
        _room
    );
    proj_cima->set_texture(&_projectile_texture);
    game_room.get_wave_manager().spawn_projectile(std::move(proj_cima));

    // Projetil de baixo
    auto proj_baixo = std::make_unique<EnemyProjectile>(
        get_position() + sf::Vector2f(0, 25), 
        shared_from_this(), 
        game_room.get_wall(), 
        _damage, 
        250.0, 
        _room
    );   
    proj_baixo->set_texture(&_projectile_texture);   
    game_room.get_wave_manager().spawn_projectile(std::move(proj_baixo));
}

bool HunterEnemy::load_texture(const std::string& file_path) {
    return _texture.loadFromFile(file_path);
}

bool HunterEnemy::load_projectile_texture(const std::string& file_path) {
    return _projectile_texture.loadFromFile(file_path);
}