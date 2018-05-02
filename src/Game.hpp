//
//  GameRoom.hpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 2018/4/20.
//

#ifndef GameRoom_hpp
#define GameRoom_hpp

#include <stdio.h>
#include "Items.hpp"
#include <map>
#include <vector>
#include "json.hpp"
#include  <string>

class Room {
private:
    std::string name;
    std::vector<std::string> room_monsters;
    std::map<std::string, Weapon> room_weapons;
    std::map<std::string, Shield> room_shields;
    Apple room_apple;
    std::map<std::string, Door> doors;

    friend void from_json(const nlohmann::json &j, Room &room);

public:
    std::string getName() { return name; };

    std::vector<std::string> &getRoomMonsters() { return room_monsters; };

    std::map<std::string, Weapon> &getRoomWeapons() { return room_weapons; };

    std::map<std::string, Shield> &getRoomShields() { return room_shields; };

    Apple &getRoomApple() { return room_apple; };

    std::map<std::string, Door> &getRoomDoors() { return doors; };

    //add a weapon to room
    void addRoomWeapon(Weapon weapon) { room_weapons[weapon.getName()] = weapon; };

    //add a shield to room
    void addRoomShield(Shield shield) { room_shields[shield.getName()] = shield; };

    //remove a weapon from room
    void removeRoomWeapon(Weapon weapon) { room_weapons.erase(weapon.getName()); };

    //remove a shield from room
    void removeRoomShield(Shield shield) { room_shields.erase(shield.getName()); };
};

class Game {
private:
    std::map<std::string, Room> rooms;
    std::map<std::string, Monster> monsters;
    std::string start_room;
    std::string end_room;

    friend void from_json(const nlohmann::json &j, Game &game_room);

public:
    std::map<std::string, Room> &getRooms();

    std::map<std::string, Monster> &getMonsters();

    const std::string &getStartRoom() const;

    const std::string &getEndRoom() const;
};

#endif /* GameRoom_hpp */
