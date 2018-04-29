#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm> 

#include <map>
#include "ofMain.h"
#include "Items.hpp"
#include "Game.hpp"
#include "Player.hpp"

enum GameState {
    IN_PROGRESS = 0,
    DUEL,
    FINISHED
};

class adventureGame : public ofBaseApp {
private:
    //image files
    std::map<std::string, ofImage> monster_pics;
    std::map<std::string, ofImage> weapon_pics;
    std::map<std::string, ofImage> shield_pics;
    ofImage door_pic;
    ofImage apple_pic;
    ofImage character;
    
public:
    Game myGame;
    Player myPlayer;
    Room current_room;
    
	// Function used for one time setup
	void setup();

	// Main event loop functions called on every frame
	void draw();
    void update();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
    
    //private helper functions
    void drawRoom(Room room);
    void drawMonster(Monster monster);
    void drawDoor(Door door);
    void drawWeapon(Weapon weapon);
    void drawShield(Shield shield);
    void drawApple(Apple apple);
    
    void drawPlayer();
    
    //determine collision
    void mapEventTrigger();
    Monster* meetMonster();
    Door* meetDoor();
    Weapon* meetWeapon();
    Shield* meetShield();
    void meetApple();
    
    //helper functions
    void changeWeapon(Weapon weapon_to_change);
    void changeShield(Shield shield_to_change);
    
    //duel functions
    void attack();
    void defense();
};
