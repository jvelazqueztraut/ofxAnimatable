//
//  ofxAnimatableFBO.h
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableObject.h"

class ofxAnimatableOfFbo : public ofxAnimatableObject {
public:
    ~ofxAnimatableOfFbo(){};
    
    void setup(int w, int h){
        fbo.allocate(w,h);
        fbo.begin();
        ofClear(0,0);
        fbo.end();
    }
    
    void begin(){
        fbo.begin();
    }
    
    void end(){
        fbo.end();
    }
    
    void draw(){
        ofxAnimatableObject::beginDraw();
        fbo.draw(0,0);
        ofxAnimatableObject::endDraw();
    }
    
    void setAnchorPercent(float xPct,float yPct){
        fbo.setAnchorPercent(xPct,yPct);
    }
    
    ofFbo       fbo;
};
