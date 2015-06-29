#include "auroraIlda1.h"

void auroraIlda1::setup(){
    etherdream.setup();
    etherdream.setPPS(30000);
    
    CenterX = 0.5;
    CenterY = 0.5;

    white = ofColor(255, 255, 255);
    color1 = ofColor(64, 64, ofRandom( 128, 255 ) );
    color2 = ofColor(ofRandom( 128, 255 ), 64, 64 );
    color3 = ofColor(64, ofRandom( 128, 255 ), ofRandom( 128, 255 ) );
    color4 = ofColor(64, 64, ofRandom( 128, 255 ) );
}

void auroraIlda1::update(){
    beat();
    
    int newScene = getSceneNumber();

    if (newScene != currentScene) //transition?
    {
        //triggerAudioFor(newScene);
        currentScene = newScene;
    }
}

void auroraIlda1::draw(){
    ofBackground(0);
    ildaFrame.clear();

    switch (currentScene) {
        case 1:
            drawScene1();
            break;

        case 2:
            drawScene2();
            break;

        case 3:
            drawScene3();
            break;

        case 4:
            drawScene4();
            break;

        default:
            ofBackground(0);
            break;
    }

    ildaFrame.update();
    ildaFrame.draw(0, 0, ofGetWidth(), ofGetHeight());
    etherdream.setPoints(ildaFrame);

    //ofSetColor(255);
    //ofDrawBitmapString(ildaFrame.getString(), 10, 30);
}

void auroraIlda1::drawScene1(){
    ofSetColor(white);

    ofPolyline circle;
    float radius = 0.05 * scale;
    circle.arc(CenterX, CenterY,
               radius, radius, 0, 360, 100);
    ildaFrame.addPoly(circle);
}

void auroraIlda1::drawScene2(){
    ofSetColor(color2);

    float radius = 0.10 * scale;
    ofPolyline circle1, circle2;
    circle1.arc(CenterX + 0.25, CenterY + 0.25,
                radius, radius, 0, 360, 100);
    circle2.arc(CenterX - 0.25, CenterY - 0.25,
                radius, radius, 0, 360, 100);

    ildaFrame.addPoly(circle1);
    ildaFrame.addPoly(circle2);
}

void auroraIlda1::drawScene3(){
    ofSetColor(color3);
    
    int numCircles = 4;
    float radius = 0.05;
    int centers[4][2] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
    
    for (int i=0; i< numCircles; i++)
    {
        ofPolyline circle;
        circle.arc(CenterX + centers[i][0]*4*radius,
                   CenterY + centers[i][1]*4*radius,
                   radius * scale, radius * scale, 0, 360, 100);

        ildaFrame.addPoly(circle);
    }
}

void auroraIlda1::drawScene4(){
}

//simulate heartbeat
void auroraIlda1::beat(){
    int heartRate = 650, beatLength = 20;
    if (ofGetElapsedTimeMillis() % heartRate < beatLength)
        scale = 0.95;
    else
        scale = 1.00;
}

int auroraIlda1::getSceneNumber(){
    int sceneTimesLength = sizeof(sceneTimes)/sizeof(sceneTimes[0]);
    for (int i=sceneTimesLength-1; i >= 0; i--)
    {
        if (ofGetElapsedTimeMillis() >= sceneTimes[i])
            return i;
    }
}

void auroraIlda1::gotMessage(ofMessage msg){
}

