//
//  Items.cpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 2018/4/21.
//

#include <stdio.h>
#include "Items.hpp"

void from_json(const nlohmann::json& j, Monster& monster) {
    monster.name = j.at("name").get<std::string>();
    monster.position_x = j.at("position_x").get<int>();
    monster.position_y = j.at("position_y").get<int>();
    monster.attack_num = j.at("attack_num").get<int>();
    monster.defence_num = j.at("defence_num").get<int>();
    monster.max_health = j.at("max_health").get<int>();
    monster.actual_health = j.at("actual_health").get<int>();
}

void from_json(const nlohmann::json& j, Weapon& weapon) {
    weapon.name = j.at("name").get<std::string>();
    weapon.position_x = j.at("position_x").get<int>();
    weapon.position_y = j.at("position_y").get<int>();
    weapon.attack_value = j.at("attack_value").get<int>();
}

void from_json(const nlohmann::json& j, Shield& shield) {
    shield.name = j.at("name").get<std::string>();
    shield.position_x = j.at("position_x").get<int>();
    shield.position_y = j.at("position_y").get<int>();
    shield.defence_value = j.at("defence_value").get<int>();
}

void from_json(const nlohmann::json& j, Apple& apple) {
    apple.position_x = j.at("position_x").get<int>();
    apple.position_y = j.at("position_y").get<int>();
}

void from_json(const nlohmann::json& j, Door& door) {
    door.name = j.at("name").get<std::string>();
    door.position_x = j.at("position_x").get<int>();
    door.position_y = j.at("position_y").get<int>();
    door.to_room = j.at("to_room").get<std::string>();
}
