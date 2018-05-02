#include "ofApp.h"
#include <iostream>

// Setup method
void adventureGame::setup() {
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
    room_name_font.load("../../../data/arial.ttf", 50);
    health_name_font.load("../../../data/arial.ttf", 25);
    button_name_font.load("../../../data/arial.ttf", 20);
    game_end_font.load("../../../data/arial.ttf", 200);

    //button set up
    attack_button = new ofxDatGuiButton("ATTACK");
    exit_button = new ofxDatGuiButton("EXIT");
    positionButtons();
    attack_button->onButtonEvent(this, &adventureGame::onButtonEvent);
    exit_button->onButtonEvent(this, &adventureGame::onButtonEvent);

    //sound set up
    punch_sound.load("../../../data/punch_sound.mp3");
    sword_sound.load("../../../data/sword_sound.mp3");
    equip_sound.load("../../../data/equip_sound.mp3");
    eat_sound.load("../../../data/eat_sound.mp3");
    win_music.load("../../../data/win_music.mp3");
    bgm.load("../../../data/bgm.mp3");
    bgm.setVolume(0.5);
    bgm.setLoop(TRUE);
    bgm.play();

    //object set up
    std::ifstream i("../../../data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    my_game = j;
    current_room = &my_game.getRooms().at(my_game.getStartRoom());
}

/*
 * draw the screen base on different game states
 */
void adventureGame::draw() {
    if (current_state == IN_PROGRESS) {
        drawRoom(current_room);
        drawPlayer();
    }

    if (current_state == DUEL) {
        drawDuelMode(target_monster);
    }

    if (current_state == LOST) {
        drawGameLost();
    }

    if (current_state == WIN) {
        drawGameWin();
    }
}

/*
 * game logic function, trigger different events
 */
void adventureGame::update() {
    if (current_state == IN_PROGRESS) {
        mapEventTrigger();
    }

    if (current_state == DUEL) {
        attack_button->update();
        exit_button->update();
    }

}

/*
 * interface to control the movement of the character
 */
void adventureGame::keyPressed(int key) {
    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }

    int upper_key = toupper(key); // Standardize on upper case
    int speed = 20;

    if (upper_key == 'A') {
        my_player.moveCharacterPosX(-speed);
    }

    if (upper_key == 'D') {
        my_player.moveCharacterPosX(speed);
    }

    if (upper_key == 'S') {
        my_player.moveCharacterPosY(speed);
    }

    if (upper_key == 'W') {
        my_player.moveCharacterPosY(-speed);
    }

    if (upper_key == 'F') {
        Weapon *weapon = meetWeapon();
        Shield *shield = meetShield();

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

/*
 * draw game room
 */
void adventureGame::drawRoom(Room *room) {
    background.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    room_name_font.drawString(room->getName(), 10, 50);
    for (auto &value: room->getRoomDoors()) {
        drawDoor(value.second);
    }

    for (auto monster_name: room->getRoomMonsters()) {
        Monster &monster_to_draw = my_game.getMonsters().at(monster_name);
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

/*
 * draw a given monster, image is retrieved from the monster_pics map
 */
void adventureGame::drawMonster(Monster monster) {
    if (monster.getName() == "" || monster.isKilled()) {
        return;
    }

    monster_pics.at(monster.getName()).draw(monster.getPositionX(), monster.getPositionY(), 100, 100);
}

/*
 * draw a given door, image is retrieved from the door_pic map
 */
void adventureGame::drawDoor(Door door) {
    door_pic.draw(door.getPositionX(), door.getPositionY(), 100, 100);
}

/*
 * draw a given weapon, images is retrieved from the weapon_pic map
 */
void adventureGame::drawWeapon(Weapon weapon) {
    if (weapon.getName() == "") {
        return;
    }
    weapon_pics.at(weapon.getName()).draw(weapon.getPositionX(), weapon.getPositionY(), 100, 100);
}

/*
 * draw a given shield, images is retrieved from the shield_pics map
 */
void adventureGame::drawShield(Shield shield) {
    if (shield.getName() == "") {
        return;
    }
    shield_pics.at(shield.getName()).draw(shield.getPositionX(), shield.getPositionY(), 100, 100);
}

/*
 * draw a given apple
 */
void adventureGame::drawApple(Apple apple) {
    apple_pic.draw(apple.getPositionX(), apple.getPositionY(), 100, 100);
}

/*
 * draw the in game player controlled character
 */
void adventureGame::drawPlayer() {
    character.draw(my_player.getPlayerPosX(), my_player.getPlayerPosY(), 100, 100);
}

//duel image functions
/*
 * draw the duel mode
 */
void adventureGame::drawDuelMode(Monster *target) {
    displayHealth();
    drawDuelPlayer();
    drawDuelMonster(target);
    ofSetColor(0, 0, 0);
    room_name_font.drawString("DUEL!", ofGetWindowWidth() / 2 - 130, 100);
    ofSetColor(255, 255, 255);

    attack_button->setWidth(200);
    exit_button->setWidth(200);
    
    button_name_font.drawString("Attack: ", 800, 620);
    button_name_font.drawString("Exit: ", 800, 770);
    
    attack_button->draw();
    exit_button->draw();
}

/*
 * draw the character
 */
void adventureGame::drawDuelPlayer() {
    character.draw(0, 430, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

/*
 * draw the monster
 */
void adventureGame::drawDuelMonster(Monster *target) {
    monster_pics.at(target->getName()).draw(700, 0, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

/*
 * display the health of both player and monster using health bar
 */
void adventureGame::displayHealth() {
    double monster_health_percent = target_monster->getActualHealth() / (double) target_monster->getMaxHealth();
    double player_health_percent = my_player.getAcutualHealth() / (double) my_player.getMaxHealth();

    ofSetColor(0, 0, 0);
    health_name_font.drawString("Player: ", 50, 190);
    health_name_font.drawString(target_monster->getName() + ": ", 50, 270);

    drawHealthBar(player_health_percent, 250, 170);
    drawHealthBar(monster_health_percent, 250, 240);
    ofSetColor(255, 255, 255);

}

/*
 * draw a given health bar
 */
void adventureGame::drawHealthBar(double percent, int pos_x, int pos_y) {
    ofSetColor(129, 131, 135);
    ofDrawRectangle(pos_x, pos_y, 300, 50);
    ofSetColor(51, 224, 24);
    ofDrawRectangle(pos_x, pos_y, 300 * percent, 50);
}

//game end image functions
/*
 * draw the game lost screen
 */
void adventureGame::drawGameLost() {
    ofSetColor(232, 6, 6);
    game_end_font.drawString("GAME \nOVER", ofGetWindowWidth() / 4, ofGetWindowHeight() / 4 + 200);
    ofSetColor(255, 255, 255);
}

/*
 * draw the game win screen
 */
void adventureGame::drawGameWin() {
    ofSetColor(255, 223, 0);
    game_end_font.drawString("YOU \n  WIN!", ofGetWindowWidth() / 4, ofGetWindowHeight() / 4 + 200);
    ofSetColor(255, 255, 255);
}

//button functions
/*
 * place the button on the screen
 */
void adventureGame::positionButtons() {
    attack_button->setPosition(900, 600);
    exit_button->setPosition(900, 750);
}

/*
 * register button to different duel functions
 */
void adventureGame::onButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target == attack_button) {
        duel(target_monster);
    }

    if (e.target == exit_button) {
        exitDuel();
    }
}

//game logic
/*
 * triggers different map events based the character's position
 */
void adventureGame::mapEventTrigger() {
    Door *door = meetDoor();
    Monster *monster = meetMonster();

    if (monster != nullptr) {          //enter duel mode if collide with monster
        target_monster = monster;
        current_state = DUEL;
        bgm.setPaused(TRUE);
        return;
    }

    if (door != nullptr && door->getName() != "") {  //move to another room if collide with door
        current_room = &my_game.getRooms().at(door->getNextRoom());
        my_player.setPlayerPosX(ofGetWindowWidth() - door->getPositionX());
        my_player.setPlayerPosY(ofGetWindowHeight() - door->getPositionY());
    }

    meetApple();
}

/*
 * replace the player weapon
 */
void adventureGame::changeWeapon(Weapon weapon_to_change) {
    equip_sound.play();

    current_room->removeRoomWeapon(weapon_to_change);
    if (my_player.getWeapon().getName() != "") {
        current_room->addRoomWeapon(my_player.getWeapon());
    }
    my_player.addWeapon(weapon_to_change);
}

/*
 * replace the player shield
 */
void adventureGame::changeShield(Shield shield_to_change) {
    equip_sound.play();

    current_room->removeRoomShield(shield_to_change);
    if (my_player.getShield().getName() != "") {
        current_room->addRoomShield(my_player.getShield());
    }
    my_player.addShield(shield_to_change);
}

/*
 * enforce the rectangle collision, return true if any part of object 1 collides with object 2
 */
bool adventureGame::rectangleCollision(int x1, int y1, int w1, int h1,
                                       int x2, int y2, int w2, int h2) {
    if (y1 + h1 < y2) {
        return false;
    }

    if (y2 + h2 < y1) {
        return false;
    }

    if (x1 + w1 < x2) {
        return false;
    }

    if (x2 + w2 < x1) {
        return false;
    }
    return true;
}

/*
 * return a pointer to the monster object if the character collides with a monster, return null otherwise
 */
Monster *adventureGame::meetMonster() {
    for (auto &monster_name: current_room->getRoomMonsters()) {
        Monster *monster = &my_game.getMonsters().at(monster_name);

        if (monster->isKilled()) { //if monster is still alive
            continue;
        }

        int player_x = my_player.getPlayerPosX();
        int player_y = my_player.getPlayerPosY();
        int monster_x = monster->getPositionX();
        int monster_y = monster->getPositionY();

        if (rectangleCollision(player_x, player_y, 100, 100, monster_x, monster_y, 100, 100)) {
            return monster;
        }
    }
    return nullptr;
}

/*
 * return a pointer to the door object if the character collides with a door, return null otherwise
 */
Door *adventureGame::meetDoor() {
    for (auto &value: current_room->getRoomDoors()) {
        Door *door = &(value.second);

        int player_x = my_player.getPlayerPosX();
        int player_y = my_player.getPlayerPosY();
        int door_x = door->getPositionX();
        int door_y = door->getPositionY();

        if (rectangleCollision(player_x, player_y, 100, 100, door_x, door_y, 100, 100)) {
            return door;
        }
    }

    return nullptr;
}

/*
 * return a pointer to the weapon object if the character collides with a weapon, return null otherwise
 */
Weapon *adventureGame::meetWeapon() {
    for (auto &value: current_room->getRoomWeapons()) {
        Weapon *weapon = &value.second;

        int player_x = my_player.getPlayerPosX();
        int player_y = my_player.getPlayerPosY();
        int weapon_x = weapon->getPositionX();
        int weapon_y = weapon->getPositionY();

        if (rectangleCollision(player_x, player_y, 100, 100, weapon_x, weapon_y, 100, 100)) {
            return weapon;
        }
    }

    return nullptr;
}

/*
 * return a pointer to the shield object if the character collides with a shield, return null otherwise
 */
Shield *adventureGame::meetShield() {
    for (auto &value: current_room->getRoomShields()) {
        Shield *shield = &value.second;

        int player_x = my_player.getPlayerPosX();
        int player_y = my_player.getPlayerPosY();
        int shield_x = shield->getPositionX();
        int shield_y = shield->getPositionY();

        if (rectangleCollision(player_x, player_y, 100, 100, shield_x, shield_y, 100, 100)) {
            return shield;
        }
    }

    return nullptr;
}

/*
 * restore the player's health if collide with an apple
 */
void adventureGame::meetApple() {
    if (current_room->getRoomApple().getPositionX() == -1 ||
        current_room->getRoomApple().isConsumed()) {
        return;
    }

    int player_x = my_player.getPlayerPosX();
    int player_y = my_player.getPlayerPosY();
    int apple_x = current_room->getRoomApple().getPositionX();
    int apple_y = current_room->getRoomApple().getPositionY();

    if (rectangleCollision(player_x, player_y, 100, 100, apple_x, apple_y, 100, 100)) {
        //reset the health
        eat_sound.play();
        my_player.setActualHealth(my_player.getMaxHealth());
        current_room->getRoomApple().consume();
    }
}

//duel mode functions
/*
 * player first attacks the given monster, then monster strikes back
 */
void adventureGame::duel(Monster *monster) {
    attack(monster);
    while (sword_sound.isPlaying());
    defense(monster);
}

/*
 * player attacks monster
 */
void adventureGame::attack(Monster *monster) {
    sword_sound.play();

    int damage = my_player.getWeapon().getAttackValue() - monster->getDefenceNum();

    if (damage > 0) {
        monster->setAcutalHealth(monster->getActualHealth() - damage);
    }

    if (monster->getActualHealth() <= 0) {
        monster->killed();
        my_player.setPlayerPosX(ofGetWindowWidth() / 2);
        my_player.setPlayerPosY(ofGetWindowHeight() / 2);

        if (target_monster->getName() == "Voldemort") { //if the final monster is defeated, the player wins
            current_state = WIN;
            win_music.setLoop(TRUE);
            win_music.play();
            return;
        }

        target_monster = nullptr;
        bgm.setPaused(FALSE);
        current_state = IN_PROGRESS; //exit the duel mode if the monster is defeated
    }

}

/*
 * the monster attacks player
 */
void adventureGame::defense(Monster *monster) {
    punch_sound.play();

    if (monster->isKilled()) {
        return;
    }

    int damage = monster->getAttackNum() - my_player.getShield().getDefenseValue();

    if (damage > 0) {
        my_player.setActualHealth(my_player.getAcutualHealth() - damage);
    }

    if (my_player.getAcutualHealth() <= 0) {  // if the player's health is less or equal to 0, the player lost the game
        bgm.setPaused(FALSE);
        current_state = LOST;
    }
}

/*
 * exit the duel mode, return to the map mode
 */
void adventureGame::exitDuel() {
    my_player.setPlayerPosX(ofGetWindowWidth() / 2);
    my_player.setPlayerPosY(ofGetWindowHeight() / 2);
    target_monster = nullptr;
    bgm.setPaused(FALSE);
    current_state = IN_PROGRESS;
}
