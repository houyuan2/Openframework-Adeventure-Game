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

//abstract class for all game items
class GameItem {
private:
    std::string name;
    int position_x;
    int position_y;
public:
    std::string getName() {return name;};
    int getPositionX() {return position_x;};
    int getPositionY() {return position_y;};
};

class Monster: public GameItem {
private:
    int attack_num;
    int defence_num;
    int max_health;
    int actual_health;
public:
    int getAttackNum() {return attack_num;};
    int getDefenceNum(){return defence_num;};
    int getMaxHealth(){return max_health;};
    int getActualHealth(){return actual_health;};
};

class Weapon: public GameItem {
private:
    int attack_value;
public:
    int getAttackValue() {return attack_value;};
};

class Shield: public GameItem {
private:
    int defence_value;
public:
    int getDefense_value() {return defence_value;};
};

class Apple: public GameItem {
    
};

class Door: public GameItem {
private:
    std::string to_room;
public:
    std::string getNextRoom() {return to_room;};
};
#endif /* Items_hpp */
