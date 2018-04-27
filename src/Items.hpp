//
//  Items.hpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 2018/4/20.
//

#ifndef Items_hpp
#define Items_hpp

#include <stdio.h>
#include <string>
#include "json.hpp"

class Monster {
private:
    std::string name;
    int position_x;
    int position_y;
    int attack_num;
    int defence_num;
    int max_health;
    int actual_health;
    bool is_dead = false;
    
    friend void from_json(const nlohmann::json& j, Monster& monster);
public:
    std::string getName() {return name;};
    int getPositionX() {return position_x;};
    int getPositionY() {return position_y;};
    int getAttackNum() {return attack_num;};
    int getDefenceNum() {return defence_num;};
    int getMaxHealth() {return max_health;};
    int getActualHealth() {return actual_health;};
    bool getState() {return is_dead;};
    void setState(bool state) {is_dead = state;};
};

class Weapon {
private:
    std::string name;
    int position_x;
    int position_y;
    int attack_value;
    
    friend void from_json(const nlohmann::json& j, Weapon& weapon);
public:
    std::string getName() {return name;};
    int getPositionX() {return position_x;};
    int getPositionY() {return position_y;};
    int getAttackValue() {return attack_value;};
};

class Shield {
private:
    std::string name;
    int position_x;
    int position_y;
    int defence_value;
    
    friend void from_json(const nlohmann::json& j, Shield& shield);
public:
    std::string getName() {return name;};
    int getPositionX() {return position_x;};
    int getPositionY() {return position_y;};
    int getDefense_value() {return defence_value;};
};

class Apple {
private:
    int position_x;
    int position_y;
    
    friend void from_json(const nlohmann::json& j, Apple& apple);
public:
    int getPositionX() {return position_x;};
    int getPositionY() {return position_y;};
};

class Door {
private:
    std::string name;
    int position_x;
    int position_y;
    std::string to_room;
    
    friend void from_json(const nlohmann::json& j, Door& door);
public:
    std::string getName() {return name;};
    int getPositionX() {return position_x;};
    int getPositionY() {return position_y;};
    std::string getNextRoom() {return to_room;};
};
#endif /* Items_hpp */
