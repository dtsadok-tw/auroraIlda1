#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"

class auroraIlda1 : public ofBaseApp{

	public:
    ofxIlda::Frame ildaFrame;
    ofxEtherdream etherdream;

    float CenterX, CenterY;

    float scale = 1.0;
    ofColor white, color1, color2, color3, color4;
    int currentScene = 0;

    const int sceneTimes[5] = {0, 1000, 3000, 6000, 9000};

    void setup();
    void update();
    void draw();

    //scenes
    int getSceneNumber();
    void drawScene1();
    void drawScene2();
    void drawScene3();
    void drawScene4();

    void beat();

    void gotMessage(ofMessage msg);
};
