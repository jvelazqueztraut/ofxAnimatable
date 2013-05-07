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

class ofxAnimatableObject {
public:
    ofxAnimatableObject();
    virtual ~ofxAnimatableObject(void){};
    
    void update(float dt);
    
    virtual void draw(){};
    
    void beginDraw();
    void endDraw();
    
    virtual void setAnchorPercent(float xPct,float yPct){};
    
    void setPosition(ofPoint p);
    void setPosition(float x, float y,float z=0.);
    
    void setSize(float s);
    
    void setColor(ofColor c);
    void setColor(int r, int g, int b, int a=255);
    void setColor(int b, int a);
    void setColor(int b);
    
    void setRotation(ofPoint r);
    void setRotation(float x, float y=0., float z=0.);
    
    bool isOrWillBeAnimating();
    
    ofxAnimatableFloat      size;
    ofxAnimatableOfColor	color;
    ofxAnimatableOfPoint	position;
    ofxAnimatableOfPoint    rotation;

};
