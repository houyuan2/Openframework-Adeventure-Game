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
#include "ofxDatGui.h"

enum GameState {
    IN_PROGRESS = 0,
    DUEL,
    LOST,
    WIN
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
    ofImage background;
    
    //font file
    ofTrueTypeFont room_name_font;
    ofTrueTypeFont health_name_font;
    
    GameState current_state = IN_PROGRESS;
    
public:
    Game myGame;
    Player my_player;
    Room* current_room;
    Monster* target_monster;
    
	// Function used for one time setup
	void setup();

	// Main event loop functions called on every frame
	void draw();
    void update();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
    
    //map image functions
    void drawRoom(Room* room);
    void drawMonster(Monster monster);
    void drawDoor(Door door);
    void drawWeapon(Weapon weapon);
    void drawShield(Shield shield);
    void drawApple(Apple apple);
    void drawPlayer();
    
    //duel image functions
    void drawDuelMode(Monster* target);
    void drawDuelPlayer();
    void drawDuelMonster(Monster *target);
    void displayHealth();
    void drawHealthBar(double percent, int pos_x, int pos_y);
    
    //button
    ofxDatGuiButton* attack_button;
    ofxDatGuiButton* exit_button;
    void positionButtons();
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    //determine collision
    void mapEventTrigger();
    bool rectangleCollision(int x1, int y1, int w1, int h1,
                            int x2, int y2, int w2, int h2);
    
    Monster* meetMonster();
    Door* meetDoor();
    Weapon* meetWeapon();
    Shield* meetShield();
    void meetApple();
    
    //helper functions
    void changeWeapon(Weapon weapon_to_change);
    void changeShield(Shield shield_to_change);
    
    //duel functions
    void duel(Monster* monster);
    void attack(Monster* monster);
    void defense(Monster* monster);
    void exitDuel();
};
