//
//  Player.hpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 4/27/18.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Items.hpp"

class Player {
private:
    int character_x = 10;
    int character_y = 800;
    Weapon player_weapon;
    Shield player_shield;
    int player_max_health = 100;
    int player_actual_health = 100;

public:
    int getPlayerPosX() { return character_x; };

    int getPlayerPosY() { return character_y; };

    void setPlayerPosX(int posX) { character_x = posX; };

    void setPlayerPosY(int posY) { character_y = posY; };

    void moveCharacterPosX(int value);

    void moveCharacterPosY(int value);

    void addWeapon(Weapon weapon) { player_weapon = weapon; };

    Weapon getWeapon() { return player_weapon; };

    void addShield(Shield shield) { player_shield = shield; };

    Shield getShield() { return player_shield; };

    int getMaxHealth() { return player_max_health; };

    void setActualHealth(int value) { player_actual_health = value; };

    int getAcutualHealth() { return player_actual_health; };
};


#endif /* Player_hpp */
