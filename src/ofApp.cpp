#include "ofApp.h"
#include <iostream>

// Setup method
void adventureGame::setup(){
	ofSetWindowTitle("Adventure");
	srand(static_cast<unsigned>(time(0)));
    
    //image loading
    myPlayer.character.load("images/character.png");
    door_pic.load("images/door.jpg");
    apple_pic.load("images/apple.jpg");
    
    ofImage knife;
    knife.load("images/knife.jpg");
    weapon_pics["knife"] = knife;
    
    ofImage sword;
    sword.load("images/sword.jpg");
    weapon_pics["sword"] = sword;
    
    ofImage laser_blade;
    laser_blade.load("images/laser_blade.png");
    weapon_pics["laser_blade"] = laser_blade;
    
    ofImage wood_shield;
    wood_shield.load("images/wood_shield.png");
    shield_pics["wood_shield"] = wood_shield;
    
    ofImage iron_shield;
    iron_shield.load("images/iron_shield.jpg");
    shield_pics["iron_shield"] = iron_shield;
    
    ofImage avalon;
    avalon.load("images/avalon.png");
    shield_pics["avalon"] = avalon;
    
    ofImage werewolf;
    werewolf.load("images/werewolf.jpg");
    monster_pics["Werewolf"] = werewolf;
    
    ofImage vampire;
    vampire.load("images/vampire.jpg");
    monster_pics["Vampire"] = vampire;
    
    ofImage zombie;
    zombie.load("images/zombie.jpg");
    monster_pics["Zombie"] = zombie;
    
    ofImage ghost;
    ghost.load("images/ghost.png");
    monster_pics["Ghost"] = ghost;
    
    ofImage voldemort;
    voldemort.load("images/voldemort.png");
    monster_pics["Voldemort"] = voldemort;
    
    //object set up
    std::ifstream i("../../../data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    myGame = j;
    current_room = myGame.getRooms().at(myGame.getStart_room());
}

void adventureGame::draw() {
    drawPlayer();
    drawRoom(current_room);
}

void adventureGame::update() {
    mapEventTrigger();
}

void adventureGame::keyPressed(int key) {
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
    for (auto monster_name: room.getRoomMonsters()) {
        Monster &monster_to_draw = myGame.getMonsters().at(monster_name);
        if (!monster_to_draw.getState()) { //if monster is still alive
            drawMonster(monster_to_draw);
        }
    }
    
    for (auto value: room.getRoomDoors()) {
        drawDoor(value.second);
    }
    
    for (auto value: room.getRoomWeapons()) {
        drawWeapon(value.second);
    }
    
    for (auto value: room.getRoomShields()) {
        drawShield(value.second);
    }
    
    Apple empty;
    if (room.getRoomApple().getPositionX() != -1 && !room.getRoomApple().getState()) {
        drawApple(room.getRoomApple());
    }
}

void adventureGame::drawMonster(Monster monster) {
    if (monster.getName() == "") {
        return;
    } monster_pics.at(monster.getName()).draw(monster.getPositionX(),monster.getPositionY(),100 ,100);
}

void adventureGame::drawDoor(Door door) {
    door_pic.draw(door.getPositionX(), door.getPositionY(),100 , 100);
}

void adventureGame::drawWeapon(Weapon weapon) {
    if (weapon.getName() == "") {
        return;
    }
    weapon_pics.at(weapon.getName()).draw(weapon.getPositionX(),weapon.getPositionY(),100 ,100);
}

void adventureGame::drawShield(Shield shield) {
    if (shield.getName() == "") {
        return;
    } shield_pics.at(shield.getName()).draw(shield.getPositionX(),shield.getPositionY(),100 ,100);
}

void adventureGame::drawApple(Apple apple) {
    apple_pic.draw(apple.getPositionX(), apple.getPositionY(), 100, 100);
}

void adventureGame::drawPlayer() {
    myPlayer.character.draw(myPlayer.character_X,myPlayer.character_Y, 100, 100);
}

//game logic
void adventureGame::mapEventTrigger() {
    Door* door = meetDoor();
    Weapon* weapon = meetWeapon();
    Shield* shield = meetShield();
    
    
    if (door != nullptr && door->getName() != "") {
        current_room = myGame.getRooms().at(door->getNextRoom());
    }
    
    if (weapon != nullptr && weapon->getName() != "") {
        changeWeapon(*weapon);
    }
    
    if (shield != nullptr && shield->getName() != "") {
        changeShield(*shield);
    }
}

void adventureGame::changeWeapon(Weapon weapon_to_change) {
    current_room.removeRoomWeapon(weapon_to_change);
    myPlayer.player_weapon = weapon_to_change;
}

void adventureGame::changeShield(Shield shield_to_change) {
    current_room.removeRoomShield(shield_to_change);
    myPlayer.player_shield = shield_to_change;
}

Monster* adventureGame::meetMonster() {
    for (auto monster_name: current_room.getRoomMonsters()) {
        Monster* monster = &myGame.getMonsters().at(monster_name);
        
        if (!monster->getState()) { //if monster is still alive
            if (myPlayer.character_X >= monster->getPositionX() && myPlayer.character_X <= monster->getPositionX() + 100 && myPlayer.character_Y >= monster->getPositionY() && myPlayer.character_Y <= monster->getPositionY() + 100) {
                return monster;
            }
        }
    }
    
    return nullptr;
}

Door* adventureGame::meetDoor() {
    for (auto value: current_room.getRoomDoors()) {
        Door* door = &value.second;
        
        if (myPlayer.character_X >= door->getPositionX() &&
            myPlayer.character_X <= door->getPositionX() + 100 &&
            myPlayer.character_Y >= door->getPositionY() &&
            myPlayer.character_Y <= door->getPositionY() + 100) {
            return door;
        }
    }
    
    return nullptr;
}

Weapon* adventureGame::meetWeapon() {
    for (auto value: current_room.getRoomWeapons()) {
        Weapon* weapon = &value.second;
        
        if (myPlayer.character_X >= weapon->getPositionX() &&
            myPlayer.character_X <= weapon->getPositionX() + 100 &&
            myPlayer.character_Y >= weapon->getPositionY() &&
            myPlayer.character_Y <= weapon->getPositionY() + 100) {
            return weapon;
        }
    }
    
    return nullptr;
}

Shield* adventureGame::meetShield() {
    for (auto value: current_room.getRoomShields()) {
        Shield* shield = &value.second;
        
        if (myPlayer.character_X >= shield->getPositionX() &&
            myPlayer.character_X <= shield->getPositionX() + 100 &&
            myPlayer.character_Y >= shield->getPositionY() &&
            myPlayer.character_Y <= shield->getPositionY() + 100) {
            return shield;
        }
    }
    
    return nullptr;
}

void adventureGame::meetApple() {
    if (current_room.getRoomApple().getPositionX() == -1) {
        return;
    }
    
    if (myPlayer.character_X >= current_room.getRoomApple().getPositionX() &&
        myPlayer.character_X <= current_room.getRoomApple().getPositionX() + 100 &&
        myPlayer.character_Y >= current_room.getRoomApple().getPositionY() &&
        myPlayer.character_Y <= current_room.getRoomApple().getPositionY() + 100) {
        
//reset the health
        myPlayer.player_actual_health = myPlayer.player_max_health;
        current_room.getRoomApple().comsume();
    }
}

void adventureGame::attack() {
    
}
void adventureGame::defense() {
    
}
