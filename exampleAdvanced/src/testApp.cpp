#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    img.loadImage("conejo1.png");
       
    img.position.setRepeatType(LOOP_BACK_AND_FORTH);
    img.position.setDuration(5.);
    img.position.animateTo(ofPoint(0.5*ofGetWidth(),0.5*ofGetHeight()));
}

//--------------------------------------------------------------
void testApp::update(){
    float dt=1./ofGetFrameRate();
    img.update(dt);
}

//--------------------------------------------------------------
void testApp::draw(){
    img.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}