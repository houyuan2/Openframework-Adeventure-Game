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

class GameRoom {
    struct Room {
        std::string name;
        std::string room_monster;
        std::vector<std::string> room_items;
        std::vector<Door> doors;
    };
    
private:
    std::vector<Room> rooms;
    std::vector<Monster> monsters;
    std::vector<GameItem> items;
};

#endif /* GameRoom_hpp */
