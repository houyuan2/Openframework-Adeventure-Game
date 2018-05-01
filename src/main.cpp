#include "ofMain.h"
#include "ofApp.h"

#define DISPLAY_MODE OF_FULLSCREEN // Can be OF_WINDOW or OF_FULLSCREEN

int main() {
    ofSetupOpenGL(1280, 960, DISPLAY_MODE); // setup the GL context
    ofSetFrameRate(30);
    ofRunApp(new adventureGame());
}
