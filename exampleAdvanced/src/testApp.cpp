#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    sprite.addFile("conejo1.png");
    sprite.addFile("conejo2.png");
    sprite.addFile("conejo3.png");
    sprite.addFile("conejo4.png");
    sprite.addFile("conejo5.png");
    sprite.addFile("conejo6.png");
    sprite.addFile("conejo5.png");
    sprite.addFile("conejo4.png");
    sprite.addFile("conejo3.png");
    sprite.addFile("conejo2.png");
    
    sprite.setFrameRate(24);
    
    sprite.play();
    
    sprite.position.setRepeatType(LOOP_BACK_AND_FORTH);
    sprite.position.setDuration(5.);
    sprite.position.animateTo(ofPoint(0.5*ofGetWidth(),0.5*ofGetHeight()));
}

//--------------------------------------------------------------
void testApp::update(){
    float dt=1./ofGetFrameRate();
    sprite.update(dt);
}

//--------------------------------------------------------------
void testApp::draw(){
    sprite.draw();
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