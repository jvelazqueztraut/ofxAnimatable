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
    
    ofPixels img;
    ofLoadImage(img,"Argentina.png");
    imgMasked.loadData(img);
    ofLoadImage(img,"Argentina Inverted.png");
    imgMasked.aux[0].loadData(img);
    imgMasked.setAnchorPercent(0.5,0.5);
    imgMasked.setPosition(512,512);
    imgMasked.setMaskType(RECTANGULAR_H);
    //imgMasked.setMaskOrientation(true);
    imgMasked.setMask(0.);
    imgMasked.aux[0].setMaskType(RECTANGULAR_H);
    //imgMasked.aux[0].setMaskOrientation(false);
    imgMasked.aux[0].setMask(0.);
    
    //PLAY
    imgMasked.aux[0].mask.setDuration(2.);
    imgMasked.aux[0].mask.setRepeatType(LOOP_BACK_AND_FORTH);
    imgMasked.aux[0].mask.animateTo(1.);
    
    imgMasked.mask.setDuration(2.);
    imgMasked.mask.setRepeatType(LOOP_BACK_AND_FORTH);
    imgMasked.mask.animateToAfterDelay(1.,5.);
    
    time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void testApp::update(){
    float t = ofGetElapsedTimef();
    float dt = t - time;
    time = t;
    img.update(dt);
    imgMasked.update(dt);
    //imgMasked.setMaskCenter(ofVec2f((float)ofGetMouseX()/ofGetWidth(),(float)ofGetMouseY()/ofGetHeight()));
    imgMasked.setPosition(ofGetMouseX(),ofGetMouseY());
}

//--------------------------------------------------------------
void testApp::draw(){
    img.draw();
    imgMasked.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(imgMasked.type){
        case RECTANGULAR_H:
            imgMasked.setMaskType(RECTANGULAR_V);
            break;
        case RECTANGULAR_V:
            imgMasked.setMaskType(CIRCULAR);
            break;
        case CIRCULAR:
            imgMasked.setMaskType(RADIAL);
            break;
        case RADIAL:
            imgMasked.setMaskType(DIAGONAL);
            break;
        case DIAGONAL:
            imgMasked.setMaskType(ARROW);
            break;
        case ARROW:
            imgMasked.setMaskType(MULTI_ARROW);
            break;
        case MULTI_ARROW:
            imgMasked.setMaskType(RECTANGLES);
            break;
        case RECTANGLES:
            imgMasked.setMaskType(HORIZONTAL);
            break;
        case HORIZONTAL:
            imgMasked.setMaskType(VERTICAL);
            break;
        case VERTICAL:
            imgMasked.setMaskType(RECTANGULAR_H);
            break;
    }
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