#include "room_manager.h"
#include <iostream>

RoomManager::RoomManager(std::string start_room_name, Room *start_room) {
    _curr_room = start_room;
    _last_room = nullptr;
    _room_map[start_room_name] = start_room;

    _curr_room->start();
}

RoomManager::~RoomManager() {
    if (_curr_room)
        _curr_room->end();
}

void RoomManager::add_room(std::string room_name, Room *room) {
    _room_map[room_name] = room;
}

void RoomManager::change_room(std::string new_room_name) {
    auto it = _room_map.find(new_room_name);
    if (it == _room_map.end()) {
        std::cerr << "Sala nao existente: \"" << new_room_name
                  << '"' << std::endl;
        return;
    }

    // se a nova sala e a mesma que a atual, nao faz nada
    if (_room_map[new_room_name] == _curr_room)
        return;

    change_room(_room_map[new_room_name]);
}

void RoomManager::change_room(Room *temp_room) {
    _last_room = _curr_room;
    _curr_room = temp_room;

    _last_room->end();
    _curr_room->start();
}

void RoomManager::rollback_room() {
    if (!_last_room) {
        std::cerr << "Nao existe sala anterior!\n";
        return;
    }

    std::swap(_curr_room, _last_room);
    _last_room->end();
    _curr_room->start();
}

void RoomManager::run(double dt) {
    if (!_curr_room) {
        std::cerr << "Ponteiro nulo para a sala atual!\n";
        return;
    }

    _curr_room->run(dt);
}