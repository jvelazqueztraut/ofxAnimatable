//
//  ofxAnimatableItem.cpp
//  exampleAdvanced
//
//  Created by Wanda on 06/05/13.
//
//

#include "ofxAnimatableItem.h"

ofxAnimatableItem::ofxAnimatableItem(){
    
	uniqueVal=ofRandom(-1000,1000);
    
    size.reset(1.);
    color.setColor(ofColor(255));
    position.setPosition(ofPoint(0.,0.,0.));
    rotation.setPosition(ofPoint(0.,0.,0.));
}

void ofxAnimatableItem::update(float dt){
    size.update(dt);
    color.update(dt);
    position.update(dt);
    rotation.update(dt);
}

void ofxAnimatableItem::beginDraw(){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(position.getCurrentPosition());
    ofRotateX(rotation.getCurrentPosition().x);
    ofRotateY(rotation.getCurrentPosition().y);
    ofRotateZ(rotation.getCurrentPosition().z);
    if(size.val()<0) ofScale(0.,0.,0.);
    else ofScale(size.val(),size.val(),size.val());
    ofSetColor(color.getCurrentColor());
}

void ofxAnimatableItem::endDraw(){
    ofPopStyle();
    ofPopMatrix();
}

void ofxAnimatableItem::setPosition(ofPoint p){
    position.setPosition(p);
}
void ofxAnimatableItem::setPosition(float x, float y,float z){
    setPosition(ofPoint(x,y,z));
}
void ofxAnimatableItem::setSize(float s){
    size.reset(s);
}

void ofxAnimatableItem::setColor(ofColor c){
    color.setColor(c);
}
void ofxAnimatableItem::setColor(int r, int g, int b, int a){
    setColor(ofColor(r,g,b,a));
}
void ofxAnimatableItem::setColor(int b, int a){
    setColor(ofColor(b,a));
}
void ofxAnimatableItem::setColor(int b){
    setColor(ofColor(b));
}
void ofxAnimatableItem::setRotation(ofPoint r){
    rotation.setPosition(r);
}
void ofxAnimatableItem::setRotation(float x, float y, float z){
    setRotation(ofPoint(x,y,z));
}

bool ofxAnimatableItem::isOrWillBeAnimating(){
    return (position.isOrWillBeAnimating() || size.isOrWillBeAnimating() || color.isOrWillBeAnimating() || rotation.isOrWillBeAnimating());
}

