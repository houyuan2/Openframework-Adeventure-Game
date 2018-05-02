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
    ofTrueTypeFont button_name_font;
    ofTrueTypeFont game_end_font;

    GameState current_state = IN_PROGRESS;
    
    //constant
    const int kRoomNameSize = 50;
    const int kHealthNameSize = 25;
    const int kButtonNameSize = 20;
    const int kGameEndFontSize = 200;
    const float kVolume = 0.5;
    const int kSpeed = 20;
    
    const int kRoomNamePosX = 10;
    const int kRoomNamePosY = 50;
    
    const int kObjectImageSize = 100;
    
    const int kDuelNamePosX = ofGetWindowWidth() / 2 - 130;
    const int kDuelnamePosY = 100;
    
    const int kButtonWidth = 200;
    
    const int kAttackNamePosX = 800;
    const int kAttackNamePosY = 620;
    
    const int kExitNamePosX = 800;
    const int kExitNamePosY = 770;
    
    const int kDuelPlayerPosX = 0;
    const int kDuelPlayerPosY = 430;
    
    const int kDuelMonsterPosX = 700;
    const int kDuelMonsterPosY = 0;
    
    const int kDuelImageSizeX = ofGetWindowWidth() / 2;
    const int kDuelImageSizeY = ofGetWindowHeight() / 2;
    
    const int kPlayerHealthNamePosX = 50;
    const int kPlayerHealthNamePosY = 190;
    
    const int kMonsterHealthNamePosX = 50;
    const int kMonsterHealthNamePosY = 270;
    
    const int kPlayerHealthBarPosX = 250;
    const int kPlayerHealthBarPosY = 170;
    
    const int kMonsterHealthBarPosX = 250;
    const int kMonsterHealthBarPosY = 240;
    
    const int kHealthBarLength = 300;
    const int kHealthBarWidth = 50;
    
    const int kGameEndPosX = ofGetWindowWidth() / 4;
    const int kGameEndPosY = ofGetWindowHeight() / 4 + 200;
    
    const int kAttackButtonPosX = 900;
    const int kAttackButtonPosY = 600;
    
    const int kExitButtonPosX = 900;
    const int kExitButtonPosY = 750;
    
    const int kScreenMidPosX = ofGetWindowWidth() / 2;
    const int kScreenMidPosY = ofGetWindowHeight() / 2;

public:
    Game my_game;
    Player my_player;
    Room *current_room;
    Monster *target_monster;

    // Function used for one time setup
    void setup();

    // Main event loop functions called on every frame
    void draw();

    void update();

    // Event driven functions, called on appropriate user action
    void keyPressed(int key);

    //map image functions
    void drawRoom(Room *room);

    void drawMonster(Monster monster);

    void drawDoor(Door door);

    void drawWeapon(Weapon weapon);

    void drawShield(Shield shield);

    void drawApple(Apple apple);

    void drawPlayer();

    //duel image functions
    void drawDuelMode(Monster *target);

    void drawDuelPlayer();

    void drawDuelMonster(Monster *target);

    void displayHealth();

    void drawHealthBar(double percent, int pos_x, int pos_y);

    //game end image functions
    void drawGameLost();

    void drawGameWin();

    //button
    ofxDatGuiButton *attack_button;
    ofxDatGuiButton *exit_button;

    void positionButtons();

    void onButtonEvent(ofxDatGuiButtonEvent e);

    //sound
    ofSoundPlayer punch_sound;
    ofSoundPlayer sword_sound;
    ofSoundPlayer equip_sound;
    ofSoundPlayer eat_sound;
    ofSoundPlayer bgm;
    ofSoundPlayer win_music;

    //determine collision
    void mapEventTrigger();

    bool rectangleCollision(int x1, int y1, int w1, int h1,
                            int x2, int y2, int w2, int h2);

    Monster *meetMonster();

    Door *meetDoor();

    Weapon *meetWeapon();

    Shield *meetShield();

    void meetApple();

    //helper functions
    void changeWeapon(Weapon weapon_to_change);

    void changeShield(Shield shield_to_change);

    bool eat_apple = false;

    //duel functions
    void duel(Monster *monster);

    void attack(Monster *monster);

    void defense(Monster *monster);

    void exitDuel();
};
