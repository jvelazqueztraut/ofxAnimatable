//
//  ofxAnimatableItem.h
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

template <class T>
class ofxAnimatableObject : public T {
public:
    ofxAnimatableObject() : T(){
        size.reset(1.);
        color.setColor(ofColor(255));
        position.setPosition(ofPoint(0.,0.,0.));
        rotation.setPosition(ofPoint(0.,0.,0.));
    }
    
    ~ofxAnimatableObject(){};
    
    void update(float dt){
        size.update(dt);
        color.update(dt);
        position.update(dt);
        rotation.update(dt);
        T::update();
    }

    void draw(){
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(position.getCurrentPosition());
        ofRotateX(rotation.getCurrentPosition().x);
        ofRotateY(rotation.getCurrentPosition().y);
        ofRotateZ(rotation.getCurrentPosition().z);
        if(size.val()<0) ofScale(0.,0.,0.);
        else ofScale(size.val(),size.val(),size.val());
        ofSetColor(color.getCurrentColor());
        T::draw(0,0);
        ofPopStyle();
        ofPopMatrix();
    }
        
    void setPosition(ofPoint p){position.setPosition(p);}
    void setPosition(float x, float y,float z=0.){setPosition(ofPoint(x,y,z));}
    
    void setSize(float s){size.reset(s);}
    
    void setColor(ofColor c){color.setColor(c);}
    void setColor(int r, int g, int b, int a=255){setColor(ofColor(r,g,b,a));}
    void setColor(int b, int a){setColor(ofColor(b,a));}
    void setColor(int b){setColor(ofColor(b));}
    
    void setRotation(ofPoint r){rotation.setPosition(r);}
    void setRotation(float x, float y=0., float z=0.){setRotation(ofPoint(x,y,z));}
    
    bool isOrWillBeAnimating(){
        return (position.isOrWillBeAnimating() || size.isOrWillBeAnimating() || color.isOrWillBeAnimating() || rotation.isOrWillBeAnimating());
    }
    
    ofxAnimatableFloat      size;
    ofxAnimatableOfColor	color;
    ofxAnimatableOfPoint	position;
    ofxAnimatableOfPoint    rotation;

};

template <class T>
class ofxAnimatableObject<T *> {
public:
    ofxAnimatableObject(){
        size.reset(1.);
        color.setColor(ofColor(255));
        position.setPosition(ofPoint(0.,0.,0.));
        rotation.setPosition(ofPoint(0.,0.,0.));
    }
    
    ~ofxAnimatableObject(){};
    
    void setPtr(T * ptr){
        _ptr=ptr;
    }
    
    void update(float dt){
        size.update(dt);
        color.update(dt);
        position.update(dt);
        rotation.update(dt);
        _ptr->update();
    }
    
    void draw(){
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(position.getCurrentPosition());
        ofRotateX(rotation.getCurrentPosition().x);
        ofRotateY(rotation.getCurrentPosition().y);
        ofRotateZ(rotation.getCurrentPosition().z);
        if(size.val()<0) ofScale(0.,0.,0.);
        else ofScale(size.val(),size.val(),size.val());
        ofSetColor(color.getCurrentColor());
        _ptr->draw(0,0);
        ofPopStyle();
        ofPopMatrix();
    }
    
    void setPosition(ofPoint p){position.setPosition(p);}
    void setPosition(float x, float y,float z=0.){setPosition(ofPoint(x,y,z));}
    
    void setSize(float s){size.reset(s);}
    
    void setColor(ofColor c){color.setColor(c);}
    void setColor(int r, int g, int b, int a=255){setColor(ofColor(r,g,b,a));}
    void setColor(int b, int a){setColor(ofColor(b,a));}
    void setColor(int b){setColor(ofColor(b));}
    
    void setRotation(ofPoint r){rotation.setPosition(r);}
    void setRotation(float x, float y=0., float z=0.){setRotation(ofPoint(x,y,z));}
    
    bool isOrWillBeAnimating(){
        return (position.isOrWillBeAnimating() || size.isOrWillBeAnimating() || color.isOrWillBeAnimating() || rotation.isOrWillBeAnimating());
    }
    T *                     _ptr;
    ofxAnimatableFloat      size;
    ofxAnimatableOfColor	color;
    ofxAnimatableOfPoint	position;
    ofxAnimatableOfPoint    rotation;
    
};

template <>
class ofxAnimatableObject<ofImage> : public ofImage {
public:
    ofxAnimatableObject() : ofImage(){
        size.reset(1.);
        color.setColor(ofColor(255));
        position.setPosition(ofPoint(0.,0.,0.));
        rotation.setPosition(ofPoint(0.,0.,0.));
    }
    
    ~ofxAnimatableObject(){};
    
    void update(float dt){
        size.update(dt);
        color.update(dt);
        position.update(dt);
        rotation.update(dt);
    }
    
    void draw(){
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(position.getCurrentPosition());
        ofRotateX(rotation.getCurrentPosition().x);
        ofRotateY(rotation.getCurrentPosition().y);
        ofRotateZ(rotation.getCurrentPosition().z);
        if(size.val()<0) ofScale(0.,0.,0.);
        else ofScale(size.val(),size.val(),size.val());
        ofSetColor(color.getCurrentColor());
        ofImage::draw(0,0);
        ofPopStyle();
        ofPopMatrix();
    }
    
    void setPosition(ofPoint p){position.setPosition(p);}
    void setPosition(float x, float y,float z=0.){setPosition(ofPoint(x,y,z));}
    
    void setSize(float s){size.reset(s);}
    
    void setColor(ofColor c){color.setColor(c);}
    void setColor(int r, int g, int b, int a=255){setColor(ofColor(r,g,b,a));}
    void setColor(int b, int a){setColor(ofColor(b,a));}
    void setColor(int b){setColor(ofColor(b));}
    
    void setRotation(ofPoint r){rotation.setPosition(r);}
    void setRotation(float x, float y=0., float z=0.){setRotation(ofPoint(x,y,z));}
    
    bool isOrWillBeAnimating(){
        return (position.isOrWillBeAnimating() || size.isOrWillBeAnimating() || color.isOrWillBeAnimating() || rotation.isOrWillBeAnimating());
    }
    
    ofxAnimatableFloat      size;
    ofxAnimatableOfColor	color;
    ofxAnimatableOfPoint	position;
    ofxAnimatableOfPoint    rotation;
    
};

template <>
class ofxAnimatableObject<ofImage *> {
public:
    ofxAnimatableObject(){
        size.reset(1.);
        color.setColor(ofColor(255));
        position.setPosition(ofPoint(0.,0.,0.));
        rotation.setPosition(ofPoint(0.,0.,0.));
    }
    
    ~ofxAnimatableObject(){};
    
    void setImage(ofImage * t){
        _ptr=t;
    }
    
    void update(float dt){
        size.update(dt);
        color.update(dt);
        position.update(dt);
        rotation.update(dt);
    }
    
    void draw(){
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(position.getCurrentPosition());
        ofRotateX(rotation.getCurrentPosition().x);
        ofRotateY(rotation.getCurrentPosition().y);
        ofRotateZ(rotation.getCurrentPosition().z);
        if(size.val()<0) ofScale(0.,0.,0.);
        else ofScale(size.val(),size.val(),size.val());
        ofSetColor(color.getCurrentColor());
        _ptr->draw(0,0);
        ofPopStyle();
        ofPopMatrix();
    }
    
    void setPosition(ofPoint p){position.setPosition(p);}
    void setPosition(float x, float y,float z=0.){setPosition(ofPoint(x,y,z));}
    
    void setSize(float s){size.reset(s);}
    
    void setColor(ofColor c){color.setColor(c);}
    void setColor(int r, int g, int b, int a=255){setColor(ofColor(r,g,b,a));}
    void setColor(int b, int a){setColor(ofColor(b,a));}
    void setColor(int b){setColor(ofColor(b));}
    
    void setRotation(ofPoint r){rotation.setPosition(r);}
    void setRotation(float x, float y=0., float z=0.){setRotation(ofPoint(x,y,z));}
    
    bool isOrWillBeAnimating(){
        return (position.isOrWillBeAnimating() || size.isOrWillBeAnimating() || color.isOrWillBeAnimating() || rotation.isOrWillBeAnimating());
    }
    ofImage *               _ptr;
    ofxAnimatableFloat      size;
    ofxAnimatableOfColor	color;
    ofxAnimatableOfPoint	position;
    ofxAnimatableOfPoint    rotation;
    
};