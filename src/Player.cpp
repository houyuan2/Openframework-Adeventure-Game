//
//  Player.cpp
//  final-project-houyuan2
//
//  Created by Houyuan Sha on 4/27/18.
//

#include "Player.hpp"

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
