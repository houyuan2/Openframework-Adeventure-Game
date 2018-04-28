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

struct Room {
    std::string name;
    std::vector<std::string> room_monsters;
    std::map<std::string, Weapon> room_weapons;
    std::map<std::string, Shield> room_shields;
    Apple room_apple;
    std::map<std::string, Door> doors;
};

class Game {
private:
    std::map<std::string, Room> rooms;
    std::map<std::string,Monster> monsters;
    std::string start_room;
    std::string end_room;
    
    friend void from_json(const nlohmann::json& j, Game& game_room);

public:
    const std::map<std::string, Room> &getRooms();

    const std::map<std::string, Monster> &getMonsters();

    const std::string &getStart_room() const;

    const std::string &getEnd_room() const;
};

#endif /* GameRoom_hpp */
