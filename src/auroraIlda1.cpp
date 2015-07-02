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

    ildaFrame.clear();

    //for (int i=0; i<4; i++)
    //    curves[i]->clear();
}

void auroraIlda1::draw(){
    ofBackground(0);

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

    genCircle(&curves[0], 0.35, CenterX, CenterY, Fuzzy);
    ildaFrame.addPoly(curves[0]);
}

void auroraIlda1::drawScene2(){
    ofSetColor(color2);

    float radius = 0.10 * scale;

    genCircle(&curves[0], radius, CenterX + 0.25, CenterX + 0.25, Fuzzy);
    ildaFrame.addPoly(curves[0]);
    genCircle(&curves[1], radius, CenterX - 0.25, CenterX - 0.25, Fuzzy);
    ildaFrame.addPoly(curves[1]);
}

void auroraIlda1::drawScene3(){
    ofSetColor(color3);
    
    int numCircles = 4;
    float radius = 0.05;
    int centers[4][2] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
    
    for (int i=0; i< numCircles; i++)
    {
        genCircle(&curves[i], radius,
                       CenterX + centers[i][0]*4*radius,
                       CenterY + centers[i][1]*4*radius, Fuzzy);

        ildaFrame.addPoly(curves[i]);
    }
}

void auroraIlda1::drawScene4(){
}

//simulate heartbeat
void auroraIlda1::beat(){
    if (ofGetElapsedTimeMillis() % HeartRate < BeatLength)
        scale = 0.85;
    else
        scale = 1.00;
}

int auroraIlda1::getSceneNumber(){
    int sceneTimesLength = sizeof(sceneTimes)/sizeof(sceneTimes[0]);
    for (int i=sceneTimesLength-1; i >= 0; i--)
    {
        if (ofGetElapsedTimeMillis() % LoopTime >= sceneTimes[i])
            return i;
    }
}

void auroraIlda1::genCircle(ofPolyline *curve,
                            float _r, float _x, float _y,
                            bool fuzzy, int resolution)
{
    curve->clear();

    for (int i=0; i< resolution; i++) {
        float j = float(i)/resolution * TWO_PI;
        float r = _r * scale;
        if (fuzzy) r *= getAmplitude();
        float x = _x + r * cos(j);
        float y = _y + r * sin(j);

        curve->curveTo(x, y);
    }
}

float auroraIlda1::getAmplitude() {
    return ofRandom(0.95, 1.05);
}

void auroraIlda1::gotMessage(ofMessage msg){
}

void auroraIlda1::keyReleased(int key) {
    if (key == ' ') Fuzzy = !Fuzzy;
}