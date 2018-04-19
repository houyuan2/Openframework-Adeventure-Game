#include "ofApp.h"
#include <iostream>

// Setup method
void adventureGame::setup(){
	ofSetWindowTitle("Adventure");

	srand(static_cast<unsigned>(time(0)));
    
    character.load("/Users/petersha/Desktop/final-project-houyuan2/src/images/character.png");
}

void adventureGame::draw(){
    character.draw(character_X,character_Y, 50, 50);
}

void adventureGame::keyPressed(int key){
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}

	int upper_key = toupper(key); // Standardize on upper case
    
    if (upper_key == 'A') {
        move_character_X(-10);
    }
    
    if (upper_key == 'D') {
        move_character_X(10);
    }
    
    if (upper_key == 'S') {
        move_character_Y(10);
    }
    
    if (upper_key == 'W') {
        move_character_Y(-10);
    }
}

void adventureGame::move_character_X(int value) {
    int new_pos = character_X + value;
    if (new_pos > ofGetWindowWidth() || new_pos < 0) {
        return;
    }
    character_X = new_pos;
    return;
}
void adventureGame::move_character_Y(int value) {
    int new_pos = character_Y + value;
    if (new_pos > ofGetWindowHeight() || new_pos < 0) {
        return;
    }
    character_Y = new_pos;
    return;
}
