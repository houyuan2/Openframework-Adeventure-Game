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

struct Player {
    ofImage character;
    int character_X = ofGetWindowWidth()/2;
    int character_Y = ofGetWindowHeight()/2;
    Weapon player_weapon;
    Shield player_shield;
    int player_max_health = 100;
    int player_actual_health = 100;
    
    void move_character_X(int value);
    void move_character_Y(int value);
};


#endif /* Player_hpp */
