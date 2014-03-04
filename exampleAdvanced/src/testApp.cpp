#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    ofEnableAlphaBlending();
    
    img.loadImage("Argentina.png");
    img.setAnchorPercent(0.5,0.5);
    img.setPosition(256,196);
    img.position.setRepeatType(LOOP_BACK_AND_FORTH);
    img.position.setDuration(2.);
    img.position.animateTo(ofPoint(768,196));
    
    imgMasked.loadImage("Argentina.png");
    imgMasked.allocate();
    imgMasked.setAnchorPercent(0.5,0.5);
    imgMasked.setPosition(512,512);
    imgMasked.setMaskType(CIRCULAR);
    imgMasked.setMask(0.);
    imgMasked.mask.setDuration(2.);
    imgMasked.mask.setRepeatType(LOOP_BACK_AND_FORTH);
    imgMasked.mask.animateTo(1.);
}

//--------------------------------------------------------------
void testApp::update(){
    float dt=1./ofGetFrameRate();
    img.update(dt);
    imgMasked.update(dt);
}

//--------------------------------------------------------------
void testApp::draw(){
    img.draw();
    imgMasked.draw();
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
    if(img.inside(ofPoint(x,y))){
        img.setRotation(0,0,0);
        img.rotation.setRepeatType(PLAY_ONCE);
        img.rotation.setDuration(3.);
        img.rotation.setCurve(LINEAR);
        img.rotation.animateTo(ofPoint(360,0,0));
    }
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