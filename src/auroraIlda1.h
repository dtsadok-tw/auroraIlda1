#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"

class auroraIlda1 : public ofBaseApp{

	public:
    ofxIlda::Frame ildaFrame;
    ofxEtherdream etherdream;

    ofPolyline curves[4];

    float CenterX, CenterY;

    float scale = 1.0;
    ofColor white, color1, color2, color3, color4;
    int currentScene = 0;

    const int sceneTimes[5] = {0, 1000, 3000, 6000, 9000};
    const int LoopTime = 12000;

    const int HeartRate = 650, BeatLength = 20;

    bool Fuzzy = true;

    void setup();
    void update();
    void draw();

    int getSceneNumber();
    void drawScene1();
    void drawScene2();
    void drawScene3();
    void drawScene4();

    void beat();
    void genCircle(ofPolyline *curve,
                   float r, float x, float y,
                   bool fuzzy = false, int resolution = 1000);
    float getAmplitude();
    void gotMessage(ofMessage msg);
    
    // audio

    // more complicated -- soundStream 
    ofSoundStream soundStream;
    void audioIn(float * input, int bufferSize, int nChannels); 
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int     bufferCounter;
    int     drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    
    // simplest - just play audio, and play images, unlinked
    
    ofSoundPlayer fullSequenceBounce;
    
    ofSoundPlayer aviPlayer;
    ofSoundPlayer sofyPlayer;
    ofSoundPlayer danPlayer;
    ofSoundPlayer normPlayer;
    
    void setupAudio();
    void triggerAudioFor(int sceneNumber);
    
    float * val;
    float * fftSmoothed;
    int nBandsToGet;
    
    float averageFft();
    void keyReleased(int key);
};
