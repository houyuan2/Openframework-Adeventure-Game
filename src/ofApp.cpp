#include "ofApp.h"
#include <iostream>

// Setup method
void adventureGame::setup(){
	ofSetWindowTitle("Adventure");
	srand(static_cast<unsigned>(time(0)));
    
    //image loading
    character.load("images/character.png");
    door_pic.load("images/door.jpg");
    apple_pic.load("images/apple.jpg");
    background.load("images/background.jpg");
    
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
    
    //font loading
    myfont.load("../../../data/arial.ttf", 50);
    
    //button set up
    attack_button = new ofxDatGuiButton("ATTACK");
    exit_button = new ofxDatGuiButton("EXIT");
    positionButtons();
    attack_button->onButtonEvent(this, &adventureGame::onButtonEvent);
    exit_button->onButtonEvent(this, &adventureGame::onButtonEvent);
    
    //object set up
    std::ifstream i("../../../data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    myGame = j;
    current_room = &myGame.getRooms().at(myGame.getStart_room());
}

void adventureGame::draw() {
    if (current_state == IN_PROGRESS) {
        drawRoom(current_room);
        drawPlayer();
    }
    
    if (current_state == DUEL) {
        drawDuelMode(target);
        attack_button->draw();
        exit_button->draw();
    }
}

void adventureGame::update() {
    if (current_state == IN_PROGRESS) {
        mapEventTrigger();
    }
    
    if (current_state == DUEL) {
        attack_button->update();
        exit_button->update();
    }
}

void adventureGame::keyPressed(int key) {
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}

	int upper_key = toupper(key); // Standardize on upper case
    int speed = 20;
    
    if (upper_key == 'A') {
        myPlayer.move_character_X(-speed);
    }
    
    if (upper_key == 'D') {
        myPlayer.move_character_X(speed);
    }
    
    if (upper_key == 'S') {
        myPlayer.move_character_Y(speed);
    }
    
    if (upper_key == 'W') {
        myPlayer.move_character_Y(-speed);
    }
    
    if (upper_key == 'F') {
        Weapon* weapon = meetWeapon();
        Shield* shield = meetShield();
        
        if (weapon != nullptr && weapon->getName() != "") {
            Weapon temp_weapon = *weapon;
            changeWeapon(temp_weapon);
        }
        
        if (shield != nullptr && shield->getName() != "") {
            Shield temp_shield = *shield;
            changeShield(temp_shield);
        }
    }
}

//map image functions
void adventureGame::drawRoom(Room* room) {
    background.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    myfont.drawString(room->getName(), 10, 50);
    for (auto &value: room->getRoomDoors()) {
        drawDoor(value.second);
    }
    
    for (auto monster_name: room->getRoomMonsters()) {
        Monster &monster_to_draw = myGame.getMonsters().at(monster_name);
        if (!monster_to_draw.isKilled()) { //if monster is still alive
            drawMonster(monster_to_draw);
        }
    }
    
    for (auto &value: room->getRoomWeapons()) {
        drawWeapon(value.second);
    }
    
    for (auto &value: room->getRoomShields()) {
        drawShield(value.second);
    }
    
    if (room->getRoomApple().getPositionX() != -1 &&
        !room->getRoomApple().isConsumed()) {
        drawApple(room->getRoomApple());
    }
}

void adventureGame::drawMonster(Monster monster) {
    if (monster.getName() == "" || monster.isKilled()) {
        return;
    }
    
    monster_pics.at(monster.getName()).draw(monster.getPositionX(),monster.getPositionY(),100 ,100);
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
    character.draw(myPlayer.getPlayerPosX() - 50, myPlayer.getPlayerPosY() - 50, 100, 100);
}

//duel image functions
void adventureGame::drawDuelMode(Monster *target) {
    drawDuelPlayer();
    drawDuelMonster(target);
}

void adventureGame::drawDuelPlayer() {
    character.draw(0, 430, ofGetWindowWidth()/2, ofGetWindowHeight()/2);
}
void adventureGame::drawDuelMonster(Monster *target) {
    monster_pics.at(target->getName()).draw(700,0,ofGetWindowWidth()/2, ofGetWindowHeight()/2);
}

//button
void adventureGame::positionButtons() {
    attack_button->setPosition(900, 700);
    exit_button->setPosition(900, 800);
}
void adventureGame::onButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target == attack_button) {
        duel(target);
    }
    
    if (e.target == exit_button) {
        exitDuel();
    }
}

//game logic
void adventureGame::mapEventTrigger() {
    Door* door = meetDoor();
    Monster* monster = meetMonster();
    
    if (monster != nullptr) {
        target = monster;
        current_state = DUEL;
        return;
    }
    
    if (door != nullptr && door->getName() != "") {
        current_room = &myGame.getRooms().at(door->getNextRoom());
        myPlayer.setPlayerPosX(ofGetWindowWidth() - door->getPositionX());
        myPlayer.setPlayerPosY(ofGetWindowHeight() - door->getPositionY());
    }
    
    meetApple();
}

void adventureGame::changeWeapon(Weapon weapon_to_change) {
    current_room->removeRoomWeapon(weapon_to_change);
    if (myPlayer.getWeapon().getName() != "") {
        current_room->addRoomWeapon(myPlayer.getWeapon());
    }
    myPlayer.addWeapon(weapon_to_change);
}

void adventureGame::changeShield(Shield shield_to_change) {
    current_room->removeRoomShield(shield_to_change);
    if (myPlayer.getShield().getName() != "") {
        current_room->addRoomShield(myPlayer.getShield());
    }
    myPlayer.addShield(shield_to_change);
}

Monster* adventureGame::meetMonster() {
    for (auto &monster_name: current_room->getRoomMonsters()) {
        Monster* monster = &myGame.getMonsters().at(monster_name);

        if (!monster->isKilled()) { //if monster is still alive
            if (myPlayer.getPlayerPosX() >= monster->getPositionX() && myPlayer.getPlayerPosX() <= monster->getPositionX() + 100 && myPlayer.getPlayerPosY() >= monster->getPositionY() && myPlayer.getPlayerPosY() <= monster->getPositionY() + 100) {
                return monster;
            }
        }
    }

    return nullptr;
}

Door* adventureGame::meetDoor() {
    for (auto &value: current_room->getRoomDoors()) {
        Door* door = &(value.second);
        
        if (myPlayer.getPlayerPosX() >= door->getPositionX() &&
            myPlayer.getPlayerPosX() <= door->getPositionX() + 100 &&
            myPlayer.getPlayerPosY() >= door->getPositionY() &&
            myPlayer.getPlayerPosY() <= door->getPositionY() + 100) {
            return door;
        }
    }
    
    return nullptr;
}

Weapon* adventureGame::meetWeapon() {
    for (auto &value: current_room->getRoomWeapons()) {
        Weapon* weapon = &value.second;
        
        if (myPlayer.getPlayerPosX() >= weapon->getPositionX() &&
            myPlayer.getPlayerPosX() <= weapon->getPositionX() + 100 &&
            myPlayer.getPlayerPosY() >= weapon->getPositionY() &&
            myPlayer.getPlayerPosY() <= weapon->getPositionY() + 100) {
            return weapon;
        }
    }
    
    return nullptr;
}

Shield* adventureGame::meetShield() {
    for (auto &value: current_room->getRoomShields()) {
        Shield* shield = &value.second;
        
        if (myPlayer.getPlayerPosX() >= shield->getPositionX() &&
            myPlayer.getPlayerPosX() <= shield->getPositionX() + 100 &&
            myPlayer.getPlayerPosY() >= shield->getPositionY() &&
            myPlayer.getPlayerPosY() <= shield->getPositionY() + 100) {
            return shield;
        }
    }
    
    return nullptr;
}

void adventureGame::meetApple() {
    if (current_room->getRoomApple().getPositionX() == -1 &&
        current_room->getRoomApple().isConsumed()) {
        return;
    }
    
    if (myPlayer.getPlayerPosX() >= current_room->getRoomApple().getPositionX() &&
        myPlayer.getPlayerPosX() <= current_room->getRoomApple().getPositionX() + 100 &&
        myPlayer.getPlayerPosY() >= current_room->getRoomApple().getPositionY() &&
        myPlayer.getPlayerPosY() <= current_room->getRoomApple().getPositionY() + 100) {
//reset the health
        myPlayer.setActualHealth(myPlayer.getMaxHealth());
        current_room->getRoomApple().consume();
    }
}

//duel mode functions
void adventureGame::duel(Monster* monster) {
    attack(monster);
    defense(monster);
}

void adventureGame::attack(Monster* monster) {
    int damage = myPlayer.getWeapon().getAttackValue() - monster->getDefenceNum();
    
    if (damage > 0) {
        monster->setAcutalHealth(monster->getActualHealth() - damage);
    }
    
    if (monster->getActualHealth() <= 0) {
        monster->killed();
        myPlayer.setPlayerPosX(ofGetWindowWidth()/2);
        myPlayer.setPlayerPosY(ofGetWindowHeight()/2);
        current_state = IN_PROGRESS;
    }
    
}
void adventureGame::defense(Monster* monster) {
    if (monster->isKilled()) {
        return;
    }
    
    int damage = monster->getAttackNum() - myPlayer.getShield().getDefense_value();
    
    if (damage > 0) {
        myPlayer.setActualHealth(myPlayer.getAcutualHealth() - damage);
    }
    
    if (myPlayer.getAcutualHealth() <= 0) {
        current_state = LOST;
    }
}

void adventureGame::exitDuel() {
    myPlayer.setPlayerPosX(ofGetWindowWidth()/2);
    myPlayer.setPlayerPosY(ofGetWindowHeight()/2);
    current_state = IN_PROGRESS;
}
