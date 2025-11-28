#include "trash_enemy.h"
#include "game_room.h"

sf::Texture TrashEnemy::_texture;

//constantes visuais
const float height = 70.0f; //lixo é menor que os outros inimigos

TrashEnemy::TrashEnemy(int base_life, int damage, int line, double speed, double base_cooldown, int points, double start_x, Room& room)
    : Enemy(base_life, damage, line, speed, base_cooldown, points, room) {

    //sobrescreve a posicao inicial padrao
    _position_x = start_x;

    //configura o shape visual
    float width = (height * _texture.getSize().x) / _texture.getSize().y;
    _shape.setSize({ width, height });
    _shape.setOrigin(sf::Vector2f(width / 2, height / 2)); //origem no centro para rodar
    _shape.setPosition(get_position());
}

bool TrashEnemy::can_walk(double next_position) {
    //pode andar ate o muro
    return next_position > WALL_POSITION_X + WALL_WIDTH;
}

void TrashEnemy::attack() {
    GameRoom& game_room = dynamic_cast<GameRoom&>(_room);

    //inimigo kamikaze q nem o fogo
    game_room.get_wall().hit(*this, _damage);

    //seta vida para 0 para ser destruido no proximo frame 
    _health.set_life(0);
}

void TrashEnemy::run(double dt) {
    Enemy::run(dt);

    //efeito de rolar: rotaciona o sprite baseado na velocidade
    float rotation_speed = -360.0f; //gira no anti-horario
    _shape.rotate(rotation_speed * dt);
}

void TrashEnemy::draw() {
    _shape.setTexture(&_texture);
    Enemy::draw();
}

bool TrashEnemy::load_texture(const std::string& file_path) {
    return _texture.loadFromFile(file_path);
}