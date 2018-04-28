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

//draw functions
void adventureGame::drawRoom(Room room) {
    for (auto monster_name: room.room_monsters) {
        Monster &monster_to_draw = myGame.getMonsters().at(monster_name);
        if (!monster_to_draw.getState()) { //if monster is still alive
            drawMonster(monster_to_draw);
        }
    }
    
    for (auto value: room.doors) {
        drawDoor(value.second);
    }
    
    for (auto value: room.room_weapons) {
        drawWeapon(value.second);
    }
    
    for (auto value: room.room_shields) {
        drawShield(value.second);
    }
    
    if (room.room_apple != NULL) {
        drawApple(room.room_apple);
    }
}

void adventureGame::drawMonster(Monster monster) {
    monster_pics.at(monster.getName()).draw(monster.getPositionX(),monster.getPositionY(),50 ,50);
}

void adventureGame::drawDoor(Door door) {
    door_pic.draw(door.getPositionX(), door.getPositionY(),50 , 50);
}

void adventureGame::drawWeapon(Weapon weapon) {
    weapon_pics.at(weapon.getName()).draw(weapon.getPositionX(),weapon.getPositionY(),50 ,50);
}

void adventureGame::drawShield(Shield shield) {
    shield_pics.at(shield.getName()).draw(shield.getPositionX(),shield.getPositionY(),50 ,50);
}

void adventureGame::drawApple(Apple apple) {
    apple_pic.draw(apple.getPositionX(), apple.getPositionY(), 50, 50);
}

void adventureGame::drawPlayer() {
    myPlayer.character.draw(myPlayer.character_X,myPlayer.character_Y, 50, 50);
}

void adventureGame::eventTrigger() {
    
}
