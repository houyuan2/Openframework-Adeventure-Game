#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm> 

#include "ofMain.h"
#include "Items.hpp"
#include "Game.hpp"
#include "Player.hpp"

class adventureGame : public ofBaseApp {
public:
    Game myGame;
    Player myPlayer;
    Room current_room;
    
    
	// Function used for one time setup
	void setup();

	// Main event loop functions called on every frame
	void draw();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
    
    //private helper functions;
    void drawRoom(Room room);
    void drawMonster(Monster monster);
    void drawDoor(Door door);
    void drawWeapon(Weapon weapon);
    void drawShield(Shield shield);
    void drawApple(Apple apple);
    void drawPlayer();
};
