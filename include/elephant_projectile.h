#include "troop_projectile.h"


class ElephantProjectile : public TroopProjectile {
private:
    double _fire_reduce; //tempo de reducao do fogo
    bool _has_extinguished = false; //flag para evitar extinguir varias vezes
    static sf::Texture _texture;
    sf::RectangleShape _shape;

protected:
    void on_hit(std::shared_ptr<Enemy> enemy) override;

public:
    ElephantProjectile(sf::Vector2f position, std::weak_ptr<Enemy> target, int damage, double speed, double fire_reduce, Room& room);

    double get_fire_reduce();
    void set_fire_reduce(double fire_reduce);

    void run(double dt) override; //override pra previnir curvas
    void draw() override;

    static bool load_texture(std::string file_path);
};