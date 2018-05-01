//
//  Player.cpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 4/27/18.
//

#include "Player.hpp"

/*
 * change the character's horizontal position, stop moving if the character is going out of the screen
 */
void Player::moveCharacterPosX(int value) {
    int new_pos = character_x + value;
    if (new_pos > ofGetWindowWidth() || new_pos < 0) {
        return;
    }
    character_x = new_pos;
    return;
}

/*
 * change the character's vertical position, stop moving if the character is going out of the screen
 */
void Player::moveCharacterPosY(int value) {
    int new_pos = character_y + value;
    if (new_pos > ofGetWindowHeight() || new_pos < 0) {
        return;
    }
    character_y = new_pos;
    return;
}
