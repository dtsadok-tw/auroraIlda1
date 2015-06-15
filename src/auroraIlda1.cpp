#include "auroraIlda1.h"

//--------------------------------------------------------------
void auroraIlda1::setup(){
    ofBackground(0);
    etherdream.setup();
    etherdream.setPPS(30000);

    color1 = ofColor(0, 0, ofRandom( 128, 255 ) );
    color2 = ofColor(ofRandom( 128, 255 ), 0, 0 );
    color3 = ofColor(0, ofRandom( 128, 255 ), ofRandom( 128, 255 ) );
    color4 = ofColor(0, 0, ofRandom( 128, 255 ) );
    
    color1.setBrightness(255);
    color2.setBrightness(255);
    color3.setBrightness(255);
    color4.setBrightness(255);

    
    //color1 = color2 = color3 = color4 = ofColor(255, 255, 255);
}

//--------------------------------------------------------------
void auroraIlda1::update(){
    //mimic heartbeat
    /*
    if (ofGetFrameNum() % 45 < 5)
        scale = 0.8;
    else
        scale = 1.0;
     */

}

void auroraIlda1::drawRandomCircle(float r0, float r1) {
    ofPolyline line;
    vector<ofPoint> points;
    
    for (float j=0; j < TWO_PI+0.1; j+= 0.05) {
        float r = 0.35 * scale * ofRandom(r0, r1);
        float x = r * cos(j) + 0.5;//+ ofGetWidth()/2;
        float y = r * sin(j) + 0.5;//+ ofGetHeight()/2;
        
        //line.addVertex(x, y); //pointy
        line.curveTo(x, y); //curvy
        //points.push_back( ofPoint(x, y));
    }
    
    //cout << "verts: " << line.getVertices().size();
    
    //line.draw();

    //ofPolyline line2(points);
    ildaFrame.addPoly(line);
    
}

//--------------------------------------------------------------
void auroraIlda1::draw(){
    ildaFrame.clear();

    //ofBackground(0);
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //ofScale(200*scale, 200*scale);
    
    ofSetColor(color1);
    drawRandomCircle(0.85, 0.85);
    
    ofSetColor(color2);
    drawRandomCircle(0.85, 1.0);
    
    ofSetColor(color3);
    drawRandomCircle(1.0, 1.25);
    
    ofSetColor(color4);
    drawRandomCircle(1.25, 1.25);

    ildaFrame.update();
    ildaFrame.draw(0, 0, ofGetWidth(), ofGetHeight());
    etherdream.setPoints(ildaFrame);

    //ofSetColor(255);
    //ofDrawBitmapString(ildaFrame.getString(), 10, 30);
}

//--------------------------------------------------------------
void auroraIlda1::keyPressed(int key){

}

//--------------------------------------------------------------
void auroraIlda1::keyReleased(int key){

}

//--------------------------------------------------------------
void auroraIlda1::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void auroraIlda1::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void auroraIlda1::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void auroraIlda1::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void auroraIlda1::windowResized(int w, int h){

}

//--------------------------------------------------------------
void auroraIlda1::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void auroraIlda1::dragEvent(ofDragInfo dragInfo){ 

}
