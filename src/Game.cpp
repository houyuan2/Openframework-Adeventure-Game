//
//  GameRoom.cpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 2018/4/20.
//

#include "Game.hpp"

/*
 * json serializer for room
 */
void from_json(const nlohmann::json &j, Room &room) {
    room.name = j.at("name").get<std::string>();
    if (j.count("room_monsters") != 0) {
        room.room_monsters = j.at("room_monsters").get<std::vector<std::string>>();
    }
    if (j.count("room_weapons") != 0) {
        room.room_weapons = j.at("room_weapons").get<std::map<std::string, Weapon>>();
    }
    if (j.count("room_shields") != 0) {
        room.room_shields = j.at("room_shields").get<std::map<std::string, Shield>>();
    }
    if (j.count("room_apple") != 0) {
        room.room_apple = j.at("room_apple").get<Apple>();
    }
    room.doors = j.at("doors").get<std::map<std::string, Door>>();
}

/*
 * json serializer for game
 */
void from_json(const nlohmann::json &j, Game &game) {
    game.rooms = j.at("rooms").get<std::map<std::string, Room>>();
    game.monsters = j.at("monsters").get<std::map<std::string, Monster>>();
    game.start_room = j.at("start_room").get<std::string>();
    game.end_room = j.at("end_room").get<std::string>();
}

std::map<std::string, Room> &Game::getRooms() {
    return rooms;
}

std::map<std::string, Monster> &Game::getMonsters() {
    return monsters;
}

const std::string &Game::getStartRoom() const {
    return start_room;
}

const std::string &Game::getEndRoom() const {
    return end_room;
}
