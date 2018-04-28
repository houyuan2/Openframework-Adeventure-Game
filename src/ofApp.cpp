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
    
    Apple empty;
    if (room.room_apple.getPositionX() != -1) {
        drawApple(room.room_apple);
    }
}

void adventureGame::drawMonster(Monster monster) {
    monster_pics.at(monster.getName()).draw(monster.getPositionX(),monster.getPositionY(),100 ,100);
}

void adventureGame::drawDoor(Door door) {
    door_pic.draw(door.getPositionX(), door.getPositionY(),100 , 100);
}

void adventureGame::drawWeapon(Weapon weapon) {
    weapon_pics.at(weapon.getName()).draw(weapon.getPositionX(),weapon.getPositionY(),100 ,100);
}

void adventureGame::drawShield(Shield shield) {
    shield_pics.at(shield.getName()).draw(shield.getPositionX(),shield.getPositionY(),100 ,100);
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
    
    
    if (door != nullptr) {
        current_room = myGame.getRooms().at(door->getNextRoom());
    }
    
    if (weapon != nullptr) {
        changeWeapon(*weapon);
    }
    
    if (shield != nullptr) {
        changeShield(*shield);
    }
}

void adventureGame::changeWeapon(Weapon weapon_to_change) {
    current_room.room_weapons[myPlayer.player_weapon.getName()] = myPlayer.player_weapon;
    myPlayer.player_weapon = weapon_to_change;
}

void adventureGame::changeShield(Shield shield_to_change) {
    current_room.room_shields[myPlayer.player_shield.getName()] = myPlayer.player_shield;
    myPlayer.player_shield = shield_to_change;
}

Monster* adventureGame::meetMonster() {
    for (auto monster_name: current_room.room_monsters) {
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
    for (auto value: current_room.doors) {
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
    for (auto value: current_room.room_weapons) {
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
    for (auto value: current_room.room_shields) {
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
    Apple &apple = current_room.room_apple;
    if (apple.getPositionX() == -1) {
        return;
    }
    
    if (myPlayer.character_X >= apple.getPositionX() &&
        myPlayer.character_X <= apple.getPositionX() + 100 &&
        myPlayer.character_Y >= apple.getPositionY() &&
        myPlayer.character_Y <= apple.getPositionY() + 100) {
        
//reset the health
        myPlayer.player_actual_health = myPlayer.player_max_health;
    }
}

void adventureGame::attack() {
    
}
void adventureGame::defense() {
    
}
