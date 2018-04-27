//
//  GameRoom.cpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 2018/4/20.
//

#include "Game.hpp"

void from_json(const nlohmann::json& j, Room& room) {
    room.name = j.at("name").get<std::string>();
    room.room_monsters = j.at("room_monsters").get<std::vector<std::string>>();
    if (j.at("room_weapons")) {
        room.room_weapons = j.at("room_weapons").get<std::map<std::string, Weapon>>();
    }
    room.room_shields = j.at("room_shields").get<std::map<std::string, Shield>>();
    room.room_apple = j.at("room_apple").get<Apple>();
    room.doors = j.at("doors").get<std::map<std::string, Door>>();
}

void from_json(const nlohmann::json& j, Game& game) {
    game.rooms = j.at("rooms").get<std::map<std::string,Room>>();
    game.monsters = j.at("monsters").get<std::map<std::string,Monster>>();
    game.start_room = j.at("start_room").get<std::string>();
    game.end_room = j.at("end_room").get<std::string>();
}

const std::map<std::string, Room> &Game::getRooms() const {
    return rooms;
}

const std::map<std::string, Monster> &Game::getMonsters() const {
    return monsters;
}

const std::string &Game::getStart_room() const {
    return start_room;
}

const std::string &Game::getEnd_room() const {
    return end_room;
}

void Player::move_character_X(int value) {
    int new_pos = character_X + value;
    if (new_pos > ofGetWindowWidth() || new_pos < 0) {
        return;
    }
    character_X = new_pos;
    return;
}
void Player::move_character_Y(int value) {
    int new_pos = character_Y + value;
    if (new_pos > ofGetWindowHeight() || new_pos < 0) {
        return;
    }
    character_Y = new_pos;
    return;
}
