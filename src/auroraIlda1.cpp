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

void auroraIlda1::setupAudio(){
    
    fullSequenceBounce.loadSound("sounds/hi_res_w_hearts.aif");
    fullSequenceBounce.setVolume(1.0f);
    fullSequenceBounce.play();
    aviPlayer.loadSound("sounds/Avi Heart#03.aif");
    aviPlayer.setVolume(1.0f);
    aviPlayer.setMultiPlay(true);
    aviPlayer.setPan(0.4);
    
    sofyPlayer.loadSound("sounds/Sofy Heart#01.aif");
    sofyPlayer.setVolume(1.0f);
    sofyPlayer.setMultiPlay(true);
    sofyPlayer.setPosition(0.5);
    sofyPlayer.setPan(0.0);
    
    danPlayer.loadSound("sounds/Pedro Heart#05.aif");
    danPlayer.setVolume(1.0f);
    danPlayer.setMultiPlay(true);
    danPlayer.setPan(-1.0);
    
    normPlayer.loadSound("sounds/Norm#02.aif");
    normPlayer.setVolume(1.0f);
    normPlayer.setMultiPlay(true);
    normPlayer.setPan(-0.4);
    
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    nBandsToGet = 128;
    
}

void auroraIlda1::update(){
    beat();
    
    int newScene = getSceneNumber();

    if (newScene != currentScene) //transition?
    {
        triggerAudioFor(newScene);
        currentScene = newScene;
    }

//    val = ofSoundGetSpectrum(nBandsToGet); // request 128 values for fft
//    for (int i = 0;i < nBandsToGet; i++){
//        // let the smoothed value sink to zero:
//        fftSmoothed[i] *= 0.96f;
//        // take the max, either the smoothed or the incoming:
//        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
//        
//    }


    ildaFrame.clear();

    //for (int i=0; i<4; i++)
    //    curves[i]->clear();

}

void auroraIlda1::draw(){
    ofBackground(0);

    switch (currentScene) {
        case 1:
            fullSequenceBounce.play();
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

void auroraIlda1::triggerAudioFor(int sceneNumber){
    switch (sceneNumber) {
        case 1:
            sofyPlayer.play();
            cout << "check avg once \n";
//            cout << averageFft();
            break;
        case 2:
            danPlayer.play();
            cout << "check avg again \n";
//            cout << averageFft();
            break;
        case 3:
            aviPlayer.play();
            cout << "check avg once agin \n";
//            cout << averageFft();
            break;
        case 4:
            normPlayer.play();
            cout << "check avg once \n";
//            cout << averageFft();
            break;
            
        default:
            break;
    }
}

float auroraIlda1::averageFft(){
    if (fftSmoothed){ cout << "true \n";}
    float sum = 0;
    for (int i = 0; i < 8192; i++){
//        cout << fftSmoothed[i];
//        sum += fftSmoothed[i];
    }
    float avg = sum / 8192;
    cout << avg;
    return avg;
}


void auroraIlda1::keyReleased(int key) {
    if (key == ' ') Fuzzy = !Fuzzy;
}

