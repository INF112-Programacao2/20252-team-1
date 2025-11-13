#include "wall.h"
#include "room_manager.h"
#include "globals.h"
#include <iostream> //!DEBUG

Wall::Wall(int base_life, int spike_damage, Room& room)
	: _health(base_life, std::bind(&Wall::destroy, this)), _spike_damage(spike_damage), _room(room) {
	_collider = sf::Rect<float>(
		sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT),
		sf::Vector2f(WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT));
};

Wall::~Wall() = default;

void Wall::destroy() {
	// Callback chamado quando a vida do muro chega a zero -> ondeathcallback
	// a ideia eh ter algo de verdade aqui -> discutir c/ grupo
	std::cout << "O muro foi de arrasta pra cima" << std::endl;
	// Se quiser remover muro da sala -> RoomManager?
	// ex: _room.remove_wall(this);
}

bool Wall::collide(sf::Vector2f position) {
	return _collider.contains(position); //isso funciona pra sprite?
	// metodo alternativo se o de cima der merda:	
	/*return position.x >= _collider.left &&
		position.x <= (_collider.left + _collider.width) &&
		position.y >= _collider.top &&
		position.y <= (_collider.top + _collider.height);*/
}

void Wall::draw_wall() {
	sf::RectangleShape wall_shape(sf::Vector2f(WALL_WIDTH, DESKTOP_SIZE.y - HUD_HEIGHT));
	wall_shape.setPosition(sf::Vector2f(WALL_POSITION_X, HUD_HEIGHT));
	wall_shape.setFillColor(sf::Color(128, 128, 128)); // cor cinza para o muro
	_room.get_window().draw(wall_shape);
}