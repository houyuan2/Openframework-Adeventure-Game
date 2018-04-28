#include "ofApp.h"
#include <iostream>

// Setup method
void adventureGame::setup(){
	ofSetWindowTitle("Adventure");
	srand(static_cast<unsigned>(time(0)));
    
    //image loading
    myPlayer.character.load("images/character.png");
    
    //object set up
    std::ifstream i("../../../data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    myGame = j;
    current_room = myGame.getRooms().at(myGame.getStart_room());
}

void adventureGame::draw(){
    drawPlayer();
}

void adventureGame::keyPressed(int key){
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}

	int upper_key = toupper(key); // Standardize on upper case
    
    if (upper_key == 'A') {
        myPlayer.move_character_X(-10);
    }
    
    if (upper_key == 'D') {
        myPlayer.move_character_X(10);
    }
    
    if (upper_key == 'S') {
        myPlayer.move_character_Y(10);
    }
    
    if (upper_key == 'W') {
        myPlayer.move_character_Y(-10);
    }
}

//helper functions
void drawRoom(Room room) {
    
}

void drawMonster(Monster monster) {
    
}
void drawDoor(Door door);
void drawWeapon(Weapon weapon);
void drawShield(Shield shield);
void drawApple(Apple apple);

void adventureGame::drawPlayer() {
    myPlayer.character.draw(myPlayer.character_X,myPlayer.character_Y, 50, 50);
}
