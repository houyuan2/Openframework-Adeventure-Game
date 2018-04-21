//
//  GameRoom.cpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 2018/4/20.
//

#include "Game.hpp"

void from_json(const nlohmann::json& j, Game& game_room) {
    game_room.rooms = j.at("rooms").get<std::map<std::string,Room>>();
    game_room.monsters = j.at("monsters").get<std::map<std::string,Monster>>();
    game_room.start_room = j.at("start_room").get<std::string>();
    game_room.end_room = j.at("end_room").get<std::string>();
}

void from_json(const nlohmann::json& j, Room& room) {
    room.name = j.at("name").get<std::string>();
    room.room_monster = j.at("room_monster").get<std::string>();
    room.room_weapons = j.at("room_weapons").get<std::map<std::string, Weapon>>();
    room.room_shields = j.at("room_shields").get<std::map<std::string, Shield>>();
    room.room_apples = j.at("room_apples").get<std::map<std::string, Apple>>();
    room.doors = j.at("doors").get<std::map<std::string, Door>>();
}
