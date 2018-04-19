#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm> 

#include "ofMain.h"

class adventureGame : public ofBaseApp {
private:
    ofImage character;
    int character_X = ofGetWindowWidth()/2;
    int character_Y = ofGetWindowHeight()/2;
public:
	// Function used for one time setup
	void setup();

	// Main event loop functions called on every frame
	void draw();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
    void move_character_X(int value);
    void move_character_Y(int value);
    
};
