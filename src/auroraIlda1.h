#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"

class auroraIlda1 : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void drawRandomCircle(float rx, float ry);
    
        float scale = 1.0;
        ofColor color1, color2, color3, color4;
        ofxIlda::Frame ildaFrame;   // stores and manages ILDA frame drawings
        ofxEtherdream etherdream;   // interface to the etherdream device

};
