//
//  ofxAnimatableFBO.h
//  exampleAdvanced
//
//  Created by jvelazqueztraut on 06/05/13.
//
//  masOTROS SRL

#pragma once

#include "ofxAnimatableObject.h"

class ofxAnimatableOfFbo : public ofxAnimatableObject, public ofFbo {
public:
    ~ofxAnimatableOfFbo(){};
    
    void setup(int w, int h){
        ofFbo::allocate(w,h);
        ofFbo::begin();
        ofClear(0,0);
        ofFbo::end();
    }
    
    void draw(){
        ofxAnimatableObject::beginDraw();
        ofFbo::draw(0,0);
        ofxAnimatableObject::endDraw();
    }
};
