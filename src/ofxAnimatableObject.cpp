//
//  ofxAnimatableItem.cpp
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#include "ofxAnimatableObject.h"

ofxAnimatableObject::ofxAnimatableObject(){
    size.reset(1.);
    color.setColor(ofColor(255));
    position.setPosition(ofPoint(0.,0.,0.));
    rotation.setPosition(ofPoint(0.,0.,0.));
}

void ofxAnimatableObject::update(float dt){
    size.update(dt);
    color.update(dt);
    position.update(dt);
    rotation.update(dt);
}

void ofxAnimatableObject::beginDraw(){
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

void ofxAnimatableObject::endDraw(){
    ofPopStyle();
    ofPopMatrix();
}

void ofxAnimatableObject::setPosition(ofPoint p){
    position.setPosition(p);
}
void ofxAnimatableObject::setPosition(float x, float y,float z){
    setPosition(ofPoint(x,y,z));
}
void ofxAnimatableObject::setSize(float s){
    size.reset(s);
}

void ofxAnimatableObject::setColor(ofColor c){
    color.setColor(c);
}
void ofxAnimatableObject::setColor(int r, int g, int b, int a){
    setColor(ofColor(r,g,b,a));
}
void ofxAnimatableObject::setColor(int b, int a){
    setColor(ofColor(b,a));
}
void ofxAnimatableObject::setColor(int b){
    setColor(ofColor(b));
}
void ofxAnimatableObject::setRotation(ofPoint r){
    rotation.setPosition(r);
}
void ofxAnimatableObject::setRotation(float x, float y, float z){
    setRotation(ofPoint(x,y,z));
}

bool ofxAnimatableObject::isOrWillBeAnimating(){
    return (position.isOrWillBeAnimating() || size.isOrWillBeAnimating() || color.isOrWillBeAnimating() || rotation.isOrWillBeAnimating());
}

