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
    fullSequenceBounce.loadSound("sounds/hi_res_w_hearts.aif");
    // fullSequenceBounce.setVolume(1.0f);
    setupAudio();

    sample.load("sounds/hi_res_w_hearts.wav");
    sample.setLooping(false);
    // 0 output channels, 
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
//    soundStream.listDevices();
    
    //if you want to set a different device id 
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;
    

    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter   = 0;
    drawCounter     = 0;
    smoothedVol     = 0.0;
    scaledVol       = 0.0;

//     soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
//    soundStream.setInput();
    ofSoundStreamSetup(2,0,this, 44100,256, 4);
    
        sample.generateWaveForm(&waveForm);


}

void auroraIlda1::setupAudio(){
    // fullSequenceBounce.play();
    sample.play();
    cout << "is lloadEd? ?";
    cout << fullSequenceBounce.isLoaded();
//    fullSequenceBounce.play();
    
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
//        triggerAudioFor(newScene);
        currentScene = newScene;
        cout << "check if loaded";
        cout << sample.getIsLoaded();
        cout << "check is playing";
        cout << sample.getIsPlaying();
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


    // sound stream read volume
    //lets scale the vol up to a 0-1 range 
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);

    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }

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

//--------------------------------------------------------------
void auroraIlda1::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0; 

    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume   
    for (int i = 0; i < bufferSize; i++){
        left[i]     = input[i*2]*0.5;
        right[i]    = input[i*2+1]*0.5;

        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :) 
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :) 
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}


