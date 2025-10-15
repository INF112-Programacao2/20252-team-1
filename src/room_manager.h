#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include "room.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

//? Talvez usar um enum ao inves de strings

// Gerencia as salas do jogo. As salas devem ser filhas de "Room" e devem ter nomes unicos
class RoomManager {
private:
    Room *_curr_room, *_last_room;
    std::unordered_map<std::string, Room *> _room_map;
    std::vector<sf::Event> _event_queue;

public:
    RoomManager(std::string start_room_name, Room *start_room);

    ~RoomManager();

    /// Adiciona uma sala nova com um nome unico
    void add_room(std::string room_name, Room *room);

    /// Muda para uma sala que ja foi salva, via nome da sala
    void change_room(std::string new_room_name);
    /// Muda para uma sala temporaria que nao e salva na memoria
    void change_room(Room *temp_rom);

    /// Muda para a ultima sala visitada (se existir)
    void rollback_room();

    /// Roda a sala atual
    void run(double dt);

    /// Adiciona eventos da window pra passar uma lista para a sala atual
    void add_event(sf::Event event);
};

#endif